#include <string>
#include "message_decoder.h"
namespace net{

	class Test :public MessageDecoder<std::string>{
	
	public :
		std::string decoder(const TcpConnectionPtr<std::string>& connection,const NetBuffer& buffer){
			std::string test="haha  test";
			return test;
		}
	
	};
}