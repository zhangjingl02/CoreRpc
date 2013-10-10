#ifndef _H_COMMON_RPC_SERVICE_SKELETON_H
#define _H_COMMON_RPC_SERVICE_SKELETON_H
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <google/protobuf/service.h>
#include "../net/tcp_connection.h"
#include "../net/service_skeleton.h"
#include "../net/message_dispatcher.h"
#include "rpc.pb.h"
namespace rpc{




	class RpcServiceSkeleton :public  net::ServiceSkeleton<TransferMessage>{
	public:
		RpcServiceSkeleton(net::MessageDispatcher<TransferMessage>* dispatcher)
			:net::ServiceSkeleton<TransferMessage>(dispatcher)
		{}
                        ~RpcServiceSkeleton(){};

		
	public :
		virtual void onMessage(net::TcpConnection& connection,boost::shared_ptr<TransferMessage> message);
		bool registService(boost::shared_ptr<google::protobuf::Service> service);
	private:
		void onLogin(Login& login);
		void onLoginRsp(LoginRsp& loginRsp);
		void onEvtBroadcastServiceList(EvtBroadcastServiceList& serviceList);
		void onRequest(Request& request);
		void onResponse(Response& response);
	private:
		std::map<std::string,boost::shared_ptr<google::protobuf::Service> > serviceMap_;

	};
}

#endif