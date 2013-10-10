#ifndef _H_NET_MESSAGE_ENCODER_H
#define _H_NET_MESSAGE_ENCODER_H
#include "../buffer/shared_buffer.h"
#include "tcp_connection.h"

namespace net{
	
	class MessageEncoder{
	
	public:
		template<typename Message>
		virtual	buffer::shared_buffer&  encode(const TcpConnectionPtr& connection,Message& message)=0;
	};
}

#endif