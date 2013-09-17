#ifndef _NET_CONNECTION_H_
#define _NET_CONNECTION_H_
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

using namespace boost::asio;
/**
**Socket Connection
**/
namespace net{

	enum ConnectionState{
		Ready,Connected,Closed,Error
		
	};

	class Connection
		: public std::enable_shared_from_this<Connection>
	{
	public:
		void send(void *message,std::size_t len);
		int id(){return socket_id_;};
		ConnectionState state(){return state_;};
	private:
		void init();

	private:
		boost::asio::ip::tcp::socket socket_;
		int socket_id_;
		ConnectionState state_;
	};
}
#endif