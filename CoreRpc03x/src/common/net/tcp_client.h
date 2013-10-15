#ifndef _H_COMMON_NET_TCP_CLIENT_H
#define _H_COMMON_NET_TCP_CLIENT_H
#include <boost/asio.hpp>
#include "tcp_connection.h"
#include "io_service_pool.h"
namespace net{

	class TcpClient{
	public:
		TcpClient(boost::asio::io_service& io_service):connection_(io_service){
			
		}
		void connect(const short port);
		void connect(const char* ip_address,const short port);
		void decoder(MessageDecoder* decoder){decoder_=decoder;};
		void encoder(MessageEncoder* encoder){encoder_=encoder;};

		void handle_connected(const boost::system::error_code& error);
		template<typename Message>
		void write(Message& message){
			connection_.write(message);
		}
	private:
		TcpConnection connection_;
		MessageDecoder* decoder_;
		MessageEncoder* encoder_;
		
	};
}
#endif 