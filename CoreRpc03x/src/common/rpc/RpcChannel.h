#ifndef _H_COMMON_RPC_RPC_CHANNEL_H
#define _H_COMMON_RPC_RPC_CHANNEL_H
#include <google/protobuf/service.h>
namespace rpc{
	
	class RpcChannel :public google::protobuf::RpcChannel{
	
	public:
		virtual void CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller,
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response,
                          google::protobuf::Closure* done);
		
	};
}

#endif 