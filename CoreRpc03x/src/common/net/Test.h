#include <string>
#include "message_decoder.h"
namespace net{

	class Test :public MessageDecoder<std::string>{
	
	public :
		std::string decoder(const TcpConnectionPtr& connection,const NetBuffer& buffer){
			std::string test="haha  test";
			return test;
		}
	
	};
}