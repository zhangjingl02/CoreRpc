#include "rpc_factory.h"


namespace rpc{

	void rpc_fatory::connect(const char* ip_address,short port){
		rpc_tcp_client_ptr client_ptr(new rpc_tcp_client(&dispatcher_,service_pool_.get_io_service()));
		client_list_.push_back(client_ptr);
		client_ptr->connect(ip_address,port);
	}

	void rpc_fatory::start(const char* ip_address,short port){
		rpc_tcp_server_ptr server_ptr(new rpc_tcp_server(&dispatcher_));
		server_list_.push_back(server_ptr);
		server_ptr->start(ip_address,port);
	}

	void rpc_fatory::start(short port){
		rpc_tcp_server_ptr server_ptr(new rpc_tcp_server(&dispatcher_));
		server_list_.push_back(server_ptr);
		server_ptr->start(port);
	}

	void rpc_fatory::regedist_service(boost::shared_ptr<google::protobuf::Service> service){
		skeleton_.registService(service);
	}


}