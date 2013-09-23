#ifndef _H_NET_TCP_SERVER_H
#define _H_NET_TCP_SERVER_H
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <boost/enable_shared_from_this.hpp>
#include "tcp_connection.h"
using boost::asio::ip::tcp;

namespace net{
	template<typename Message>
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


	private:
		template<typename Message>
		void start_accept()
		{
			//TcpConnectionPtr new_session(new TcpConnection(io_service_));//=new TcpConnection(io_service_);
			TcpConnection<Message>* new_session=new TcpConnection<Message>(io_service_);
			Test * decoder=new Test();
			new_session->decoder();
			acceptor_.async_accept(new_session->socket(),
				boost::bind(&TcpServer::handle_accept, this, new_session,
				boost::asio::placeholders::error));
		}

		void handle_accept(TcpConnection<Message>* new_session,
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
	};
}
#endif