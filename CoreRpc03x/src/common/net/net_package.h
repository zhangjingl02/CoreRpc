#ifndef _H_COMMON_NET_NETWORK_PACKAGE_H
#define _H_COMMON_NET_NETWORK_PACKAGE_H
#include "tcp_connection.h"
namespace net{

	template<typename T>
	class NetworkPackage{
	public:
		NetworkPackage(TcpConnection& connection)
			:connection_(connection){}

		 TcpConnection& connection(){return connection_;};
		
		 void message(boost::shared_ptr<T> message){message_=message;};
	
		 boost::shared_ptr<T> message(){return message_;};
	private:
		TcpConnection& connection_;
		boost::shared_ptr<T> message_;
	
	};
	
}
#endif