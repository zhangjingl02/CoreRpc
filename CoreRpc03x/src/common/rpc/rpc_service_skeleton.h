#ifndef _H_COMMON_RPC_SERVICE_SKELETON_H
#define _H_COMMON_RPC_SERVICE_SKELETON_H
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <google/protobuf/service.h>
#include "../net/tcp_connection.h"
#include "../net/service_skeleton.h"
#include "../net/message_dispatcher.h"
#include "../net/cache_manager.h"
#include "rpc.pb.h"
#include "rpc_common.h"
#include "rpc_channel.h"
namespace rpc{


	class RpcCallBack:public google::protobuf::Closure{
		public:
			~RpcCallBack();

			 void Run() ;
	};

	//public static final int SUCCESS=0;
	//public static final int ERR_NOT_FOUND_SERVICE=1;
	//public static final int ERR_NOT_FOUND_METHOD=2;
	//public static final int ERR_PARAM=3;
	//public static final int ERR_SERVICE_EXCEPTION=4;
	//public static final int ERR_TIME_OUT=5;
	//public static final int ERR_CLIENT_NOT_LOGIN=6;
	
	typedef std::map<std::string,boost::shared_ptr<google::protobuf::Service> > service_map;
	class RpcServiceSkeleton :public  net::ServiceSkeleton<TransferMessage>{
	public:
		RpcServiceSkeleton(RpcChannel* rpc_channel,net::MessageDispatcher<TransferMessage>* dispatcher,net::cache_manager<int,Response>& cache_manager)
			:net::ServiceSkeleton<TransferMessage>(dispatcher),cache_manager_(cache_manager),rpc_channel_(rpc_channel)
		{}
		~RpcServiceSkeleton(){};


	public :
		virtual void onMessage(net::tcp_connection& connection,boost::shared_ptr<TransferMessage> message);
		bool registService(boost::shared_ptr<google::protobuf::Service> service);
	private:
		void onLogin(net::tcp_connection& connection,Login& login);
		void onLoginRsp(net::tcp_connection& connection,LoginRsp& loginRsp);
		void onEvtBroadcastServiceList(net::tcp_connection& connection,EvtBroadcastServiceList& serviceList);
		void onRequest(net::tcp_connection& connection,Request& request);
		void onResponse(net::tcp_connection& connection,boost::shared_ptr<Response>& rsp_ptr);
		std::string getServiceList();

	private:
		service_map serviceMap_;
		net::cache_manager<int,Response>& cache_manager_;
		RpcChannel* rpc_channel_;

	};
}

#endif