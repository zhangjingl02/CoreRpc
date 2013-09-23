#ifndef _H_NET_MESSAGE_DECODER_H
#define _H_NET_MESSAGE_DECODER_H
#include "tcp_connection.h"
#include "net_buffer.h"
namespace net{
	template<typename Message>
	class MessageDecoder{

	public:
		template<typename Message>
		Message decoder(const TcpConnectionPtr<Message>& connection,const NetBuffer& buffer )=0;

	};
}

#endif