#include "tcp_server.h"
#include "../common.h"
namespace net{

	TcpServer::TcpServer(boost::asio::io_service& io_service)
		:io_service_(io_service),acceptor_(io_service, boost::asio::ip::tcp::endpoint(
		boost::asio::ip::tcp::v4(),
        9898)),endpoint_(boost::asio::ip::tcp::endpoint(
        boost::asio::ip::tcp::v4(),
        9898)),connection_(io_service),socket_(io_service)
	{


	}

	void TcpServer::start(const char* ip_address,const short port){
		LOG_INF(_KV_(ip_address,port));
		//boost::asio::ip::tcp::endpoint endpoint(address::from_string(ip_address),port);
		//acceptor_.open(endpoint.protocol());
		//acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		//acceptor_.bind(endpoint);
		//acceptor_.listen();
		do_accept();

	}

	void TcpServer::do_accept(){
		//ConnectionPtr connection_ptr(new Connection(io_service_));
		//tcp::socket socket(io_service_);
		acceptor_.async_accept(socket_,endpoint_,
			
			[this](boost::system::error_code error){
				
				if(!error){
					LOG_INF(_KV_("message","accept connection success"));
					std::make_shared<Connection>(io_service_,std::move(socket_))->receive();
				
				}else{
					LOG_INF(_KV_("message","accept connection failed:")<<error.value()<<"|"<<
						error.message()
						);
				}
				//do_accept();
		}
		
		//boost::bind(&TcpServer::accept_connection,this,boost::asio::placeholders::error)
		);
	}

	void TcpServer::accept_connection(const boost::system::error_code& error){
		if(!error){
					LOG_INF(_KV_("message","accept connection success"));
				}else{
					LOG_INF(_KV_("message","accept connection failed:")<<error.value()<<"|"<<
						error.message()
			);
		}
				do_accept();
	}

}