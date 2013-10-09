#include "../common.h"
#include "rpc_service_skeleton.h"

namespace rpc{


	bool RpcServiceSkeleton::registService(boost::shared_ptr<google::protobuf::Service> service){
		//serviceMap_.insert(std::make_pair(service.GetDescriptor()->full_name(),service));
		return false;
	}


	void RpcServiceSkeleton::onMessage(net::TcpConnectionPtr connection,boost::shared_ptr<TransferMessage> message){
	
		switch (message->command())
		{
		case TransferMessage_Command_Request:{
			Request request=message->request();
			onRequest(request);
			break;
											 }
			
		case TransferMessage_Command_Response:
		case TransferMessage_Command_Login:{
			Login login;
			login.ParseFromString(message->message());
			onLogin(login);break;
										   }
		case TransferMessage_Command_EvtBroadcastServiceList:
		case TransferMessage_Command_EvtActiveTest:
		case TransferMessage_Command_LoginRsp:
			
		default:
			break;
		}
	
	}

	void RpcServiceSkeleton::onRequest(Request& request){}
	void RpcServiceSkeleton::onLogin(Login& login){
		LOG_INF(_KV_("on Login",login.username()));
	}


}