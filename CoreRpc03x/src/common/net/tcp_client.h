#ifndef _H_COMMON_NET_TCP_CLIENT_H
#define _H_COMMON_NET_TCP_CLIENT_H
#include "tcp_connection.h"
namespace net{

	class TcpClient{
	public:
		bool connect(const short port);
		bool connect(const char* ip_address,const short port);

	private:
		TcpConnection connection_;
		
	};
}
#endif 