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
			Response rsp_message=message->response();
			onResponse(connection,rsp_message);
			break;
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
		TransferMessage tm;
		
		Response rsp;
		rsp.set_id(request.id());
		tm.set_command(TransferMessage_Command_Response);
	
		boost::shared_ptr<google::protobuf::Service> service_ptr=serviceMap_[request.servicename()];
		if(service_ptr){
			const google::protobuf::MethodDescriptor* method=service_ptr->GetDescriptor()->FindMethodByName(request.methodname());
			if(method){
				google::protobuf::Message* message=service_ptr->GetRequestPrototype(method).New();
				if(message->ParseFromString(request.message())){
					 google::protobuf::Message* response=service_ptr->GetResponsePrototype(method).New();
					 service_ptr->CallMethod(method,NULL,message,response,NULL);
					 rsp.set_errorcode(RpcError::SUCCESS);
					 rsp.set_errormessage("success");
					 rsp.set_message(response->SerializeAsString());
				}else{
					rsp.set_errorcode(RpcError::ERR_PARAM);
					rsp.set_errormessage("param error");
				}
			}else{
				rsp.set_errorcode(RpcError::ERR_NOT_FOUND_METHOD);
				rsp.set_errormessage("not found method");
			}
		}else{
			rsp.set_errorcode(RpcError::ERR_NOT_FOUND_SERVICE);
			rsp.set_errormessage("not found service");
		}
		tm.set_allocated_response(&rsp);
		connection.write(tm);
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

	void RpcServiceSkeleton::onResponse(net::tcp_connection& connection,Response& response){
	
	}
}