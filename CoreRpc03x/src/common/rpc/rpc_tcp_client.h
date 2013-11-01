#ifndef _H_COMMON_RPC_TCP_CLIENT_H
#define _H_COMMON_RPC_TCP_CLIENT_H
#include <boost/shared_ptr.hpp>

#include "../net/tcp_client.h"
namespace rpc{
	class rpc_tcp_client:public net::tpc_client{
	public:
		rpc_tcp_client(boost::asio::io_service& io_service):
			tpc_client(io_service){}
	private:

	};

	typedef boost::shared_ptr<rpc_tcp_client> rpc_tcp_client_ptr;
}

#endif