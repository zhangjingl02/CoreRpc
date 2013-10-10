#ifndef _H_NET_MESSAGE_ENCODER_H
#define _H_NET_MESSAGE_ENCODER_H
#include "../buffer/shared_buffer.h"
#include "tcp_connection.h"

namespace net{
	
	class MessageEncoder{
	
	public:
		
		virtual	buffer::shared_buffer&  encode(void* message)=0;
	};
}

#endif