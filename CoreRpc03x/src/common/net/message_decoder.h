#ifndef _H_NET_MESSAGE_DECODER_H
#define _H_NET_MESSAGE_DECODER_H
#include "tcp_connection.h"
#include "net_buffer.h"
namespace net{
	
	class TcpConnection;
	class MessageDecoder{
	
	public:
		virtual  void decode(const TcpConnection& connection, NetBuffer& buffer)=0;
	
		
	
	};
}

#endif