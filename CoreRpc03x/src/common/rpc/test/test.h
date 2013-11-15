#ifndef _H_COMMON_RPC_TEST_h
#define _H_COMMON_RPC_TEST_h
#include "RpcTest.pb.h"
namespace rpc{
  
	class  Test: public rpc::test::TestService{
	virtual void subscribe(::google::protobuf::RpcController* controller,
                       const ::rpc::test::Request* request,
                       ::rpc::test::Response* response,
					   ::google::protobuf::Closure* done){

						   response->set_code("test");
						   response->set_desc("haha  test success");
						   printf("subscribe:%s",request->phone().c_str());

	
	}
  virtual void unSubscribe(::google::protobuf::RpcController* controller,
                       const ::rpc::test::Request* request,
                       ::rpc::test::Response* response,
					   ::google::protobuf::Closure* done){
  
  
  }
		
	};
}
#endif