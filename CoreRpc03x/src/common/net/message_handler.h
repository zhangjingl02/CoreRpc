#ifndef _H_NET_MESSAGE_HANDLER_H
#define _H_NET_MESSAGE_HANDLER_H
#include "tcp_connection.h"
namespace net{
	template<typename Message>
	class MessageHanlder{
	
	public:
		void connectionActive(const TcpConnectionPtr& connection)=0;
		template<typename Message>
		void messageReceived(const TcpConnectionPtr& connection,Message& message)=0;
		

	
	};
}
#endif