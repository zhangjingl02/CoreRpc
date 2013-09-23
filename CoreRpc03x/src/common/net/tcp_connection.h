#ifndef _H_NET_TCP_CONNECTION_H
#define _H_NET_TCP_CONNECTION_H
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "net_buffer.h"
using boost::asio::ip::tcp;
namespace net{
	class TcpConnection
	{
	public:
		TcpConnection(boost::asio::io_service& io_service)
			: socket_(io_service)
		{
		}

		tcp::socket& socket()
		{
			return socket_;
		}

		void start()
		{
			socket_.async_read_some(boost::asio::buffer(data_, max_length),
				boost::bind(&TcpConnection::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}

	private:

		
		void handle_read(const boost::system::error_code& error,
			size_t bytes_transferred)
		{
			if (!error)
			{
				boost::asio::async_write(socket_,
					boost::asio::buffer(data_, bytes_transferred),
					boost::bind(&TcpConnection::handle_write, this,
					boost::asio::placeholders::error));
			}
			else
			{
				delete this;
			}
		}

		void handle_write(const boost::system::error_code& error)
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

		tcp::socket socket_;
		enum { max_length = 1024 };
		char data_[max_length];
		NetBuffer buffer_;
	};

	typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
}
#endif
