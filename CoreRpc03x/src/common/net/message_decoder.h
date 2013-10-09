#ifndef _H_NET_MESSAGE_DECODER_H
#define _H_NET_MESSAGE_DECODER_H

#include "tcp_connection.h"
#include "net_buffer.h"

namespace net{
	
	class TcpConnection;
	
	class MessageDecoder{

		
	public:
		//MessageDecoder(){};
		//virtual MessageDecoder(MessageDecoder* other);
	public:
		virtual int decode(TcpConnection& connection, NetBuffer& buffer)=0;
	};
}

#endif