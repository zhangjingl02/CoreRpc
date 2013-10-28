#include "../common.h"
#include "rpc_service_skeleton.h"

namespace rpc{


	bool RpcServiceSkeleton::registService(boost::shared_ptr<google::protobuf::Service> service){
		serviceMap_.insert(std::make_pair(service->GetDescriptor()->full_name(),service));
		return true;
	}




	void RpcServiceSkeleton::onMessage(net::tcp_connection& connection,boost::shared_ptr<TransferMessage> message){
	
		switch (message->command())
		{
		case TransferMessage_Command_Request:{
			Request request=message->request();
			onRequest(connection,request);
			break;
											 }
			
		case TransferMessage_Command_Response:
		case TransferMessage_Command_Login:{
			Login login;
			login.ParseFromString(message->message());
			onLogin(connection,login);break;
										   }
		case TransferMessage_Command_EvtBroadcastServiceList:
		case TransferMessage_Command_EvtActiveTest:
		case TransferMessage_Command_LoginRsp:
			
		default:
			break;
		}
	
	}

	void RpcServiceSkeleton::onRequest(net::tcp_connection& connection,Request& request){
		boost::shared_ptr<google::protobuf::Service> service_ptr=serviceMap_[request.servicename()];
		if(service_ptr){
			const google::protobuf::MethodDescriptor* method=service_ptr->GetDescriptor()->FindMethodByName(request.methodname());
			if(method){
				google::protobuf::Message* message=service_ptr->GetRequestPrototype(method).New();
				if(message->ParseFromString(request.message())){
					 google::protobuf::Message* response=service_ptr->GetResponsePrototype(method).New();
					 service_ptr->CallMethod
				}else{
				}
			}else{
			
			}
		}else{
		
		}
	}
	void RpcServiceSkeleton::onLogin(net::tcp_connection& connection,Login& login){
		LOG_INF(_KV_("on Login",login.username()));

		TransferMessage tm;
		tm.set_command(TransferMessage_Command_LoginRsp);
		LoginRsp loginRsp;
		loginRsp.set_status("0");
		std::string str;
		loginRsp.SerializeToString(&str);
		tm.set_message(str);
		connection.write(tm);

	}


}