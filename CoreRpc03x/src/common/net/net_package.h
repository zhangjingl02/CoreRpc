#ifndef _H_COMMON_NET_NETWORK_PACKAGE_H
#define _H_COMMON_NET_NETWORK_PACKAGE_H
#include "tcp_connection.h"
namespace net{

	template<typename T>
	class NetworkPackage{
	
	public:
		TcpConnectionPtr connection;
		boost::shared_ptr<T> message;
	
	};
	
}
#endif