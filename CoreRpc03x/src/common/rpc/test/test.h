#ifndef _H_COMMON_RPC_TEST_h
#define _H_COMMON_RPC_TEST_h
#include "RpcTest.pb.h"
namespace rpc{
  
	class  Test{
	
		void test(){
		
			rpc::test::TestService_Stub stub();

		}
	};
}
#endif