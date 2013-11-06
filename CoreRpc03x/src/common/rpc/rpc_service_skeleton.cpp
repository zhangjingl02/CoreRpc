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
			Request request;
			request.ParseFromString(message->message());
			onRequest(connection,request);
			break;
											 }
			
		case TransferMessage_Command_Response:{
			boost::shared_ptr<Response> rsp_ptr(new Response());
			rsp_ptr->ParseFromString(message->message());
			onResponse(connection,rsp_ptr);
											  }
			break;
		case TransferMessage_Command_Login:{
			Login login;
			login.ParseFromString(message->message());
			onLogin(connection,login);break;
										   }
		
		case TransferMessage_Command_LoginRsp:{
			LoginRsp loginRsp;
			loginRsp.ParseFromString(message->message());
			onLoginRsp(connection,loginRsp);
			break;
			}

		case TransferMessage_Command_EvtBroadcastServiceList:
			{
				EvtBroadcastServiceList serviceList;
				serviceList.ParseFromString(message->message());
				onEvtBroadcastServiceList(connection,serviceList);
				break;
			}
		case TransferMessage_Command_EvtActiveTest:		
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
		tm.set_message(rsp.SerializeAsString());
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

		TransferMessage tmBoastServiceList;
		tmBoastServiceList.set_command(TransferMessage_Command_EvtBroadcastServiceList);
		tmBoastServiceList.set_message(getServiceList());
		connection.write(tmBoastServiceList);

	}
	void RpcServiceSkeleton::onLoginRsp(net::tcp_connection& connection,LoginRsp& loginRsp){
		LOG_INF(_KV_("message","onLoginRsp"));
		if(loginRsp.status()=="0"){
		
		}
	
	}
	void RpcServiceSkeleton::onResponse(net::tcp_connection& connection,boost::shared_ptr<Response>& response){
		LOG_INF(_KV_("message","onResponse"));
		net::cache_message<Response>* cache_message=cache_manager_.find(response->id());
		if(cache_message){
			cache_message->run(response);
		}else{
			LOG_INF(_KV_("message","onResponse,but miss request message:")<<response->id());
		}
		
	}

	void RpcServiceSkeleton::onEvtBroadcastServiceList(net::tcp_connection& connection,EvtBroadcastServiceList& serviceList){
		LOG_INF(_KV_("message","onEvtBroadcastServiceList")
			<<_KV_("id:",connection.id())
			);
		for(int i=0;i<serviceList.service_size();i++){
			ServiceInfo info=serviceList.service().Get(i);
			rpc_channel_->addConnection(info.servicename(),net::tcp_connection_ptr(&connection));
		}

	}

	std::string RpcServiceSkeleton::getServiceList(){
		
		EvtBroadcastServiceList serviceList;
		for(service_map::iterator it=serviceMap_.begin();it!=serviceMap_.end();it++){
			ServiceInfo* s_info=serviceList.add_service();
			s_info->set_servicename(it->second.get()->GetDescriptor()->full_name());
			s_info->set_methodname("");
		}
		return  serviceList.SerializePartialAsString();
	}
}