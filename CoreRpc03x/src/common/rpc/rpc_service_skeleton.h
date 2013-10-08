#ifndef _H_COMMON_RPC_SERVICE_SKELETON_H
#define _H_COMMON_RPC_SERVICE_SKELETON_H
#include <boost/shared_ptr.hpp>
#include "../net/service_skeleton.h"
#include "../net/message_dispatcher.h"
#include "rpc.pb.h"
namespace rpc{
	class RpcServiceSkeleton :public  net::ServiceSkeleton<TransferMessage>{
	public:
		RpcServiceSkeleton(net::MessageDispatcher<TransferMessage>* dispatcher)
			:net::ServiceSkeleton<TransferMessage>(dispatcher)
		{}
	public :
		virtual void onMessage(boost::shared_ptr<TransferMessage> message){};

	};
}

#endif