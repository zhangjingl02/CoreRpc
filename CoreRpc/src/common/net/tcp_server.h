/* 
 * File:   tcp_server.h
 * Author: Administrator
 *
 * Created on 2013年9月22日, 上午11:06
 */

#ifndef _NET_TCP_SERVER_H
#define	_NET_TCP_SERVER_H
#include <vector>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "connection.h"
using namespace boost::asio::ip;
namespace net{
	class TcpServer
	{

		public:
			explicit TcpServer(boost::asio::io_service& io_service);
        public:
            void start(const char* ip_address,const short prot);
            
        private:
			void do_accept();
		private:
			void accept_connection(const boost::system::error_code& error);

            tcp::acceptor acceptor_;
			std::vector<ConnectionPtr>  clients_;
			boost::asio::io_service& io_service_;
			Connection connection_;
			boost::asio::ip::tcp::endpoint endpoint_;
			boost::asio::ip::tcp::socket socket_;
	};
}


#endif	/* _NET_TCP_SERVER_H */

