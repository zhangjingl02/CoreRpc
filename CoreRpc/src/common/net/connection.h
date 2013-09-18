#ifndef _NET_CONNECTION_H_
#define _NET_CONNECTION_H_
#include <boost/asio.hpp>
#include<boost/enable_shared_from_this.hpp>

using namespace boost::asio;
/**
**Socket Connection
**/
namespace net{

	enum ConnectionState{
		Ready,Connected,Closed,Error
		
	};

	class Connection
		: public boost::enable_shared_from_this<Connection>
	{

	public:
		explicit Connection(boost::asio::io_service& io_service);
	public:
		size_t send(const void *message,std::size_t len);
		size_t send(const char *message,std::size_t len);
		int id()const {return socket_id_;};
		ConnectionState state()const {return state_;};
		boost::asio::ip::tcp::socket& socket()  {return socket_;}
		bool connect(const char* ip_address,const char* port);
	private:
		void init();
		void connect_handler(const boost::system::error_code& error);
		void do_read();

	private:
		boost::asio::ip::tcp::socket socket_;
		int socket_id_;
		boost::asio::ip::tcp::resolver resolver_;
		ConnectionState state_;
	};
}
#endif