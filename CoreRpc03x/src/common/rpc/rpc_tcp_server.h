#ifndef _H_COMMON_RPC_RPC_TCP_SERVER_H
#define _H_COMMON_RPC_RPC_TCP_SERVER_H
#include <boost/shared_ptr.hpp>
#include "../net/message_dispatcher.h"
#include "../net/tcp_server.h"
#include "rpc.pb.h"
namespace rpc{

	class rpc_tcp_server£º public net::tcp_server{
	
	public:
		rpc_tcp_server(net::MessageDispatcher<TransferMessage>* dispatcher,std::size_t pool_size)
			:dispatcher_(dispatcher),tcp_server(pool_size)
	private:
		net::MessageDispatcher<TransferMessage>* dispatcher_;
	};

	typedef boost::shared_ptr<rpc_tcp_server> rpc_tcp_server_ptr;

}
#endif 