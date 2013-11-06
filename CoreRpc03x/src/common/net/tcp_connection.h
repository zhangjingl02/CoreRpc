#ifndef _H_NET_TCP_CONNECTION_H
#define _H_NET_TCP_CONNECTION_H
#include <cstdlib>
#include <iostream>
#include <vector>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/ref.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "../buffer/shared_buffer_list.h"
#include "../common.h"
#include "message_decoder.h"
#include "message_encoder.h"
#include "net_buffer.h"
#include "net_def.h"
#include "../util/sequence_generator.h"
using boost::asio::ip::tcp;
namespace net{

	// typedef boost::function<void (const TcpConnectionPtr&,const boost::system::error_code&) > CloseCallback;
	typedef boost::function<void (const boost::system::error_code&) > ConnectedCallback;
	typedef boost::function<void (int id,const boost::system::error_code&) > CloseCallback;
	class MessageDecoder;

	#define DEFAULT_HEADE_SIZE 5
	class tcp_connection:public boost::enable_shared_from_this<tcp_connection>
	{
	public:
		tcp_connection(boost::asio::io_service& io_service)
			: socket_(io_service),service_(io_service),sending_(false),id_( kConnectionId.next()),buffer_(new NetBuffer())
		{
			
		}

		tcp::socket& socket()
		{
			return socket_;
		}

		void start()
		{
			read();
		}

		void stop(){};
		
		void decoder(message_decoder* decoder){
			messageDecoder_=decoder;
		}

		void encoder(message_encoder* encoder){
			messageEncoder_=encoder;
		}

		void write(buffer::shared_buffer& buffer){
			service_.post(boost::bind(&tcp_connection::post_wirte,this,buffer));
		};
		template<typename Message>
		void write(Message message){
			if(messageEncoder_){
				buffer::shared_buffer buffer(0);
				if(messageEncoder_->encode(&message,buffer)){
					write(buffer);
				}
				
			}
			
		}

		void connect(const short port){
			socket_.async_connect(tcp::endpoint(boost::asio::ip::tcp::v4(),port),
				boost::bind(&tcp_connection::handle_connected,this,boost::asio::placeholders::error)
				);
		}

		void connect(const char* ip_address,const short port){
			socket_.async_connect(tcp::endpoint(boost::asio::ip::address_v4::from_string(ip_address),port),
				boost::bind(&tcp_connection::handle_connected,this,boost::asio::placeholders::error));
		}

		void set_connected_callback(const ConnectedCallback& connected_callback){
			connected_callback_=connected_callback;
		}

		tcp::endpoint& local_endpoint(){
			return socket_.local_endpoint();
		}

		tcp::endpoint& remote_endpoint(){
			return socket_.remote_endpoint();
		}

		void add_close_callback(const CloseCallback& callback){
			close_callbacks.push_back(callback);
		}
		
		int id(){return id_;}

	private:

		void read(){
			socket_.async_read_some(boost::asio::buffer(data_, max_length),
				boost::bind(&tcp_connection::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}

	
		void post_wirte(buffer::shared_buffer& buffer){
			bufferList_.push(buffer);
			do_write();
		}

		void do_write(){
		
			if(!sending_&& !bufferList_.empty()){
				sending_=true;
				socket_.async_write_some(buffer::buffer(bufferList_),
					boost::bind(&tcp_connection::handle_write,this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
			}
			
		}
		void handle_read(const boost::system::error_code& error,
			size_t bytes_transferred)
		{
			if (!error)
			{
				buffer_->append(data_,bytes_transferred);
				if(messageDecoder_){
					if(net::RECV_SUCCESS== messageDecoder_->decode(*this,*buffer_)){
					
						buffer_->retrieveAll();
					}
				}
				read();
			}
			else
			{
				handle_error(error);
				//delete this;
			}
		}
		

		void handle_write(const boost::system::error_code& error, std::size_t bytes_transferred  )
		{
			if (!error)
			{
				sending_ = false;
				bufferList_.remove(bytes_transferred);
				do_write();
			}
			else
			{
				handle_error(error);
				delete this;
			}
		}

		void handle_connected(const boost::system::error_code& error){
			
			if(!error){
				start();
				LOG_INF(_KV_("message","connected to server")
					<<"["<<socket_.local_endpoint().address().to_string()
					<<":"<<socket_.local_endpoint().port()
					<<"=>"
					<<socket_.remote_endpoint().address().to_string()
					<<":"
					<<socket_.remote_endpoint().port()
					<<"]"
					);
				if(!connected_callback_){
					connected_callback_(error);
				}
			}else{
				LOG_INF(_KV_("message","connect to server failed")
					<<"["
					<<error.value()
					<<":"
					<<error.message()
					<<"]"
					);
			}
			if(connected_callback_){
				connected_callback_(error);
			}
		}

		void handle_error(const boost::system::error_code& error){
			if(error){
				LOG_INF(_KV_("message","handler socket error")
					<<_KV_("error:",error.value())
					<<"|"<<error.message()
					);
				for(int i=0;i<close_callbacks.size();i++){
					if(close_callbacks[i]){
						close_callbacks[i](id_,error);
					}
				}

			}
		}

		
	private:
		tcp::socket socket_;
		enum { max_length = 1024 };
		char data_[max_length];
		boost::asio::io_service& service_;
		NetBuffer* buffer_;
		message_decoder* messageDecoder_;
		message_encoder* messageEncoder_;
		buffer::shared_buffer_list bufferList_;
		bool sending_;
		int id_;
		std::vector<CloseCallback> close_callbacks;
		ConnectedCallback connected_callback_;
		public:
		static util::SequenceGenerator kConnectionId;
	};
	 

	typedef boost::shared_ptr<tcp_connection> tcp_connection_ptr;
}
#endif
