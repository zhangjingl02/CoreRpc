#ifndef _H_NET_MESSAGE_ENCODER_H
#define _H_NET_MESSAGE_ENCODER_H
#include "tcp_connection.h"
namespace net{
	template<typename Message>
	class MessageEncoder{
	
	public:
		template<typename Message>
		void encode(const TcpConnectionPtr& connection,Message& message)=0;
	};
}

#endif