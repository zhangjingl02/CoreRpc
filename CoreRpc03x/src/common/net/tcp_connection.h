#ifndef _H_NET_TCP_CONNECTION_H
#define _H_NET_TCP_CONNECTION_H
#include <cstdlib>
#include <iostream>
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

using boost::asio::ip::tcp;
namespace net{

	// typedef boost::function<void (const TcpConnectionPtr&,const boost::system::error_code&) > CloseCallback;
	typedef boost::function<void (const boost::system::error_code&) > ConnectedCallback;
	class MessageDecoder;

	#define DEFAULT_HEADE_SIZE 5
	class TcpConnection:public boost::enable_shared_from_this<TcpConnection>
	{
	public:
		TcpConnection(boost::asio::io_service& io_service)
			: socket_(io_service),service_(io_service),sending_(false)
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
		
		void decoder(MessageDecoder* decoder){
			messageDecoder_=decoder;
		}

		void encoder(MessageEncoder* encoder){
			messageEncoder_=encoder;
		}

		void write(buffer::shared_buffer& buffer){
			service_.post(boost::bind(&TcpConnection::post_wirte,this,buffer));
		};
		template<typename Message>
		void write(Message& message){
			if(messageEncoder_){
				buffer::shared_buffer buffer(0);
				if(messageEncoder_->encode(&message,buffer)){
					write(buffer);
				}
				
			}
			
		}

		void connect(const short port){
			socket_.async_connect(tcp::endpoint(boost::asio::ip::tcp::v4(),port),
				boost::bind(&TcpConnection::handle_connected,this,boost::asio::placeholders::error)
				
				);
		}

		void connect(const char* ip_address,const short port){
			socket_.async_connect(tcp::endpoint(boost::asio::ip::address_v4::from_string(ip_address),port),
				boost::bind(&TcpConnection::handle_connected,this,boost::asio::placeholders::error));
		}

		void set_connected_callback(ConnectedCallback& connected_callback){
			connected_callback_=connected_callback;
		}
		


	private:

		void read(){
			socket_.async_read_some(boost::asio::buffer(data_, max_length),
				boost::bind(&TcpConnection::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}

		void read_body(buffer::shared_buffer& buffer){
			//boost::asio::async_read
			//socket_.async_receive();
		socket_.async_receive(buffer::buffer(buffer),
				boost::bind(&TcpConnection::handle_read_body, this,
				boost::asio::placeholders::error,boost::ref(buffer),
				boost::asio::placeholders::bytes_transferred));
		}
		
		void post_wirte(buffer::shared_buffer& buffer){
			bufferList_.push(buffer);
			do_write();
		}

		void do_write(){
		
			if(!sending_&& !bufferList_.empty()){
				socket_.async_write_some(buffer::buffer(bufferList_),
					boost::bind(&TcpConnection::handle_write,this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
			}
		}
		void handle_read(const boost::system::error_code& error,
			size_t bytes_transferred)
		{
			if (!error)
			{
				buffer_.append(data_,bytes_transferred);
				if(messageDecoder_){
					messageDecoder_->decode(*this,buffer_);
				}
				read();
			}
			else
			{
				//delete this;
			}
		}
		void handle_read_body(const boost::system::error_code& error,buffer::shared_buffer& buffer,
			size_t bytes_transferred){
		
				if(!error){
					buffer.remove(bytes_transferred);
					if(0<buffer.size()){
						read_body(buffer);
						return;
					}

					buffer.restore();
					//messageDecoder_->decode(*this,buffer,bytes_transferred);
					read();
				}
		}

		void handle_write(const boost::system::error_code& error, std::size_t bytes_transferred  )
		{
			if (!error)
			{
				socket_.async_read_some(boost::asio::buffer(data_, max_length),
					boost::bind(&TcpConnection::handle_read, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
			}
			else
			{
				delete this;
			}
		}

		void handle_connected(const boost::system::error_code& error){

			if(!error){
				
				LOG_INF(_KV_("message","connected to server")
					<<"["<<socket_.local_endpoint().address().to_string()
					<<":"<<socket_.local_endpoint().port()
					<<"=>"
					<<socket_.remote_endpoint().address().to_string()
					<<":"
					<<socket_.remote_endpoint().port()
					<<"]"
					);
			}else{
				LOG_INF(_KV_("message","connect to server failed")
					<<"["
					<<socket_.remote_endpoint().address().to_string()
					<<":"
					<<socket_.remote_endpoint().port()
					<<"]"
					);
			}
			if(connected_callback_){
				connected_callback_(error);
			}
		}
	private:
		tcp::socket socket_;
		enum { max_length = 1024 };
		char data_[max_length];
		boost::asio::io_service& service_;
		NetBuffer buffer_;
		MessageDecoder* messageDecoder_;
		MessageEncoder* messageEncoder_;
		buffer::shared_buffer_list bufferList_;
		bool sending_;
		int id_;
		ConnectedCallback connected_callback_;
	};

	typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
}
#endif
