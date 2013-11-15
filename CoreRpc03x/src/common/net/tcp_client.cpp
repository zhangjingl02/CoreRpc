#include "tcp_client.h"

namespace net{

	void tpc_client::connect(const short port){
		connection_.connect(port);
	}
	void tpc_client::connect(const char* ip_address,const short port){
		connection_.connect(ip_address,port);
	}
}