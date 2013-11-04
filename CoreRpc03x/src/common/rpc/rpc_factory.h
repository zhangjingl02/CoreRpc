#ifndef _H_COMMON_RPC_FACTORY_H
#define _H_COMMON_RPC_FACTORY_H
#include <vector>
#include "../net/io_service_pool.h"
#include "../net/message_dispatcher.h"
#include "rpc.pb.h"
#include "rpc_channel.h"
#include "rpc_service_skeleton.h"
#include "rpc_tcp_client.h"
#include "rpc_tcp_server.h"
namespace rpc{
	class rpc_fatory{
	public:
		rpc_fatory():service_pool_(5),skeleton_(&dispatcher_,cache_manager_),channel_(cache_manager_)
		{
			service_pool_.run();
			skeleton_.start();
		}
		void connect(const char* ip_address,short port);
		void start(const char* ip_address,short port);
		void start(short port);
		void regedist_service(boost::shared_ptr<google::protobuf::Service> service);

		const RpcChannel* channel() const{return &channel_;} ;
		RpcChannel* channel(){return &channel_;};

	private:
		net::MessageDispatcher<TransferMessage> dispatcher_;
		RpcServiceSkeleton skeleton_;
		RpcChannel channel_;
		std::vector<rpc_tcp_client_ptr> client_list_;
		std::vector<rpc_tcp_server_ptr> server_list_;
		net::io_service_pool service_pool_;
		net::cache_manager<int,Response> cache_manager_;
	};
}


#endif