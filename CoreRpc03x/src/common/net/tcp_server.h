#ifndef _H_NET_TCP_SERVER_H
#define _H_NET_TCP_SERVER_H
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <boost/enable_shared_from_this.hpp>
#include "../rpc/protobuf_decoder.h"
#include "io_service_pool.h"
#include "tcp_connection.h"

using boost::asio::ip::tcp;

namespace net{
	class tcp_server:public boost::enable_shared_from_this<tcp_server>
	{
	public:
		tcp_server(std::size_t pool_size)
			:io_service_pool_(pool_size)
			//,acceptor_(ioServicePool_.get_io_service())
		{
			acceptor_=new tcp::acceptor(io_service_pool_.get_io_service());
			io_service_pool_.run();
		}




		//TcpServer(IoServicePool& service_pool)
		//	: 
		//	ioServicePool_(service_pool),acceptor_(ioServicePool_.get_io_service())
		//{
		//	ioServicePool_.run();
		//}


		~tcp_server(){
			io_service_pool_.stop();
			delete acceptor_;
		}

		void start(const char* ip_address,const short port);
		void start(const short port);

		void decoder(message_decoder* decoder){decoder_=decoder;};
		void encoder(message_encoder* encoder){encoder_=encoder;};
		virtual void on_accepted(tcp_connection_ptr& new_session){};
	private:
		void start_accept()
		{
			tcp_connection_ptr new_session(new tcp_connection(io_service_pool_.get_io_service()));//=new TcpConnection(io_service_);
			//TcpConnection* new_session=new TcpConnection(ioServicePool_.get_io_service());
			new_session->decoder(decoder_);
			new_session->encoder(encoder_);
			acceptor_->async_accept(new_session->socket(),
				boost::bind(&tcp_server::handle_accept, this, new_session,
				boost::asio::placeholders::error));
		}

		void handle_accept(tcp_connection_ptr& new_session,
			const boost::system::error_code& error)
		{
			if (!error)
			{
				LOG_INF(_KV_("message","accepted new session [")
					<<new_session->remote_endpoint().address().to_string()
					<<":"
					<<new_session->remote_endpoint().port()
					<<"=>"
					<<new_session->local_endpoint().address().to_string()
					<<":"
					<<new_session->local_endpoint().port()
					<<"]"
					);
				new_session->start();
				on_accepted(new_session);
			}
			else
			{
				LOG_INF(_KV_("message","accepted new session [")
					<<error.value()
					<<":"<<error.message()
					<<"]"
					);
			}
			start_accept();
			
		}
	private:
		
		//boost::asio::io_service& io_service_;
		tcp::acceptor* acceptor_;
		message_decoder* decoder_;
		message_encoder* encoder_;
		io_service_pool io_service_pool_;
		
	};
}
#endif