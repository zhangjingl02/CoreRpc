#include "tcp_client.h"

namespace net{

	void TcpClient::connect(const short port){
		connection_.connect(port);
	}
	void TcpClient::connect(const char* ip_address,const short port){
		connection_.connect(ip_address,port);
	}
}