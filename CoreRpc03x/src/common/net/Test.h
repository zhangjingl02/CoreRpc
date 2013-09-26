#include <string>
#include "message_decoder.h"
namespace net{

	class Test :public MessageDecoder{
	
	public :
		void decoder(const TcpConnection& connection, NetBuffer& buffer){
			std::string test="haha  test";
			
		}
	
	};
}