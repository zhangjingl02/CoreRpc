#ifndef _H_COMMON_NET_NETWORK_PACKAGE_H
#define _H_COMMON_NET_NETWORK_PACKAGE_H
#include "tcp_connection.h"
namespace net{

	template<typename T>
	class NetworkPackage{
	public:
		NetworkPackage(tcp_connection& connection)
			:connection_(connection){}

		 tcp_connection& connection(){return connection_;};
		
		 void message(boost::shared_ptr<T> message){message_=message;};
	
		 boost::shared_ptr<T> message(){return message_;};
	private:
		tcp_connection& connection_;
		boost::shared_ptr<T> message_;
	
	};
	
}
#endif