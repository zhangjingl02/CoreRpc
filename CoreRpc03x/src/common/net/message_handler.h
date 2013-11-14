#ifndef _H_NET_MESSAGE_HANDLER_H
#define _H_NET_MESSAGE_HANDLER_H
#include "tcp_connection.h"
namespace net{
	template<typename Message>
	class MessageHanlder{
	
	public:
		void connectionActive(const tcp_connection_ptr& connection)=0;
		template<typename Message>
		void messageReceived(const tcp_connection_ptr& connection,Message& message)=0;
		

	
	};
}
#endif