#include <string>
#include "message_decoder.h"
namespace net{

	class Test :public message_decoder{
	
	public :
		void decoder(const tcp_connection& connection, NetBuffer& buffer){
			std::string test="haha  test";
			
		}
	
	};
}