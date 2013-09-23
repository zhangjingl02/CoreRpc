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
	template<typename Message>
	class TcpConnection:public boost::enable_shared_from_this<TcpConnection>
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
			read();
		}
		template<typename Message>
		void decoder(MessageDecoder<Message>* decoder){
			messageDecoder_=decoder;
		}

	private:

		void read(){
		socket_.async_read_some(boost::asio::buffer(data_, max_length),
				boost::bind(&TcpConnection::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
		void handle_read(const boost::system::error_code& error,
			size_t bytes_transferred)
		{
			if (!error)
			{

				buffer_.append(&data_,bytes_transferred);
				messageDecoder_->decode(shared_from_this(),buffer_);
				read();
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
		template<typename Message>
		MessageDecoder<Message>* messageDecoder_;
	};
	template<typename Message>
	typedef boost::shared_ptr<TcpConnection<Message>> TcpConnectionPtr;
}
#endif
