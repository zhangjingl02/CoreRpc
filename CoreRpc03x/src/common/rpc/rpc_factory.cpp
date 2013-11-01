#include "rpc_factory.h"


namespace rpc{

	void rpc_fatory::connect(const char* ip_address,short port){
		rpc_tcp_client_ptr client_ptr(new rpc_tcp_client());
	}

	void rpc_fatory::start(const char* ip_address,short port){
	
	}

	void rpc_fatory::start(short port){
	
	}
}