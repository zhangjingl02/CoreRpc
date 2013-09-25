#ifndef _H_NET_TCP_CONNECTION_H
#define _H_NET_TCP_CONNECTION_H
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "message_decoder.h"
#include "net_buffer.h"
#include "../buffer/shared_buffer.h"
#include "../common.h"
using boost::asio::ip::tcp;
namespace net{
	class MessageDecoder;
	class TcpConnection:boost::enable_shared_from_this<TcpConnection>
	{
	public:
		TcpConnection(boost::asio::io_service& io_service)
			: socket_(io_service),buffer(4096)
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
		
		void decoder(MessageDecoder* decoder){
			messageDecoder_=decoder;
		}

	private:

		void read(){
			socket_.async_read_some(buffer::buffer(buffer),
				boost::bind(&TcpConnection::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
		
		void handle_read(const boost::system::error_code& error,
			size_t bytes_transferred)
		{
			if (!error)
			{
				if(bytes_transferred==0){read();}else{
				
				LOG_INF("read size:"<<buffer.capacity()<<"|"<<bytes_transferred);
				//messageDecoder_->decode(*this,buffer_);
				read();}
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
		buffer::uint8 data2_[max_length];
		NetBuffer buffer_;
		buffer::shared_buffer buffer;
		MessageDecoder* messageDecoder_;
	};

	typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
}
#endif
