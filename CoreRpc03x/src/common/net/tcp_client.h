#ifndef _H_COMMON_NET_TCP_CLIENT_H
#define _H_COMMON_NET_TCP_CLIENT_H
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "tcp_connection.h"
#include "io_service_pool.h"
namespace net{

	class tpc_client{
	public:
		tpc_client(boost::asio::io_service& io_service):connection_(io_service){
			connection_.set_connected_callback(boost::bind(&tpc_client::on_connected,this,_1));
		}
		void connect(const short port);
		void connect(const char* ip_address,const short port);
		void decoder(message_decoder* decoder){connection_.decoder(decoder);};
		void encoder(message_encoder* encoder){connection_.encoder(encoder);};

		virtual void on_connected(const boost::system::error_code& error){};
		template<typename Message>
		void write(Message& message){
			connection_.write(message);
		}
	private:
		tcp_connection connection_;
		message_decoder* decoder_;
		message_encoder* encoder_;
		
	};
}
#endif 