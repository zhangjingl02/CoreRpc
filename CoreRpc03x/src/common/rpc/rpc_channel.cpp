#include "rpc_channel.h"
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "rpc.pb.h"
#include "rpc_call_back.h"
#include "rpc_common.h"
namespace rpc{


	void RpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller,
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response,
						  google::protobuf::Closure* done){

			TransferMessage tm;
			tm.set_command(TransferMessage_Command_Request);
			Request req;
			req.set_servicename(method->service()->full_name());
			req.set_methodname(method->full_name());
			req.set_id(sequence_gen_.next());
			req.set_message(request->SerializeAsString());
			tm.set_allocated_request(&req);

			net::tcp_connection_ptr connection_ptr=	get_connection(method->service()->full_name());
			if(!connection_ptr)
			{
				LOG_INF(_KV_("message","not found rpc connection"));
				return;
			}



			rpc_call_back call_back;
			net::cache_message<Response> cacheMessage(call_back);
			cache_manager_.put(req.id(),&cacheMessage);
			connection_ptr->write(tm);
			while(!cacheMessage.is_done()){

				
				cacheMessage.wait(5000);
				
			}
			
			Response* rsp=cacheMessage.response();
			if(rsp){
				if(rsp->errorcode()==RpcError::SUCCESS){
					response->ParseFromString(rsp->message());
				}
			}



			



	
	}

	net::tcp_connection_ptr RpcChannel::get_connection(const std::string& service_name){
		connections_map::iterator it=connections_map_.find("TestService");
		if(it!=connections_map_.end()){
			return it->second.front();
		}
		return net::tcp_connection_ptr();
	}
}