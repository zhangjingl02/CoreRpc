#include "rpc_channel.h"
#include "rpc.pb.h"

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

			net::tcp_connection_ptr connection_ptr=	get_connection();
			if(!connection_ptr)
			{
				LOG_INF(_KV_("message","not found rpc connection"));
				return;
			}

			connection_ptr->write(tm);



			



	
	}

	net::tcp_connection_ptr RpcChannel::get_connection(){
		if(connections_.size==0){
			return net::tcp_connection_ptr();
		}
		return connections_[0];
	}
}