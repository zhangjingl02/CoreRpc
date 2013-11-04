#ifndef _H_NET_MESSAGE_DECODER_H
#define _H_NET_MESSAGE_DECODER_H
#include <boost/shared_ptr.hpp>
#include "tcp_connection.h"
#include "net_buffer.h"
#include "../buffer/shared_buffer.h"
namespace net{
	
	class tcp_connection;
	typedef boost::shared_ptr<tcp_connection> tcp_connection_ptr;
	class message_decoder{

		
	public:
		//MessageDecoder(){};
		//virtual MessageDecoder(MessageDecoder* other);
	public:
		virtual int decode(tcp_connection& connection, net::NetBuffer& buffer)=0;
		//virtual int decode(TcpConnection& connection, buffer::shared_buffer& buffer,std::size_t size)=0;
		//virtual std::size_t frameDecode(TcpConnection& connection, buffer::shared_buffer& buffer,std::size_t size)=0;
	};
}

#endif