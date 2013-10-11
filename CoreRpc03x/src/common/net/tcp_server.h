#ifndef _H_NET_TCP_SERVER_H
#define _H_NET_TCP_SERVER_H
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include 
#include <boost/enable_shared_from_this.hpp>

#include "tcp_connection.h"
#include "../rpc/protobuf_decoder.h"
using boost::asio::ip::tcp;

namespace net{
	class TcpServer
	{
	public:
		TcpServer(boost::asio::io_service& io_service)
			: io_service_(io_service),
			acceptor_(io_service)
		{
			//start_accept();
		}

		void start(const char* ip_address,const short port);
		void start(const short port);

		void decoder(MessageDecoder* decoder){decoder_=decoder;};
		void encoder(MessageEncoder* encoder){encoder_=encoder;};

	private:
		void start_accept()
		{
			//TcpConnectionPtr new_session(new TcpConnection(io_service_));//=new TcpConnection(io_service_);
			TcpConnection* new_session=new TcpConnection(io_service_);
			new_session->decoder(decoder_);
			new_session->encoder(encoder_);
			acceptor_.async_accept(new_session->socket(),
				boost::bind(&TcpServer::handle_accept, this, new_session,
				boost::asio::placeholders::error));
		}

		void handle_accept(TcpConnection* new_session,
			const boost::system::error_code& error)
		{
			if (!error)
			{
				std::cout<<"accepted new session"<<std::endl;
				new_session->start();
				
			}
			else
			{
				std::cout<<"accept new session failed"<<std::endl;
				//delete new_session;
			}
			start_accept();
			
		}
	private:
		
		boost::asio::io_service& io_service_;
		tcp::acceptor acceptor_;
		MessageDecoder* decoder_;
		MessageEncoder* encoder_;
	};
}
#endif