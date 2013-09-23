
#include <cstdlib>
#include <iostream>
#include "../common.h"
#include "connection.h"
using namespace boost::asio::ip;
namespace net {

    Connection::Connection(boost::asio::io_service& io_service) : resolver_(io_service),
    socket_(io_service) {

    }

	Connection::Connection(boost::asio::io_service& io_service,boost::asio::ip::tcp::socket socket) : resolver_(io_service)
    ,socket_(io_service) 
	{

   }

    size_t Connection::send(const void *message, std::size_t len) {
        return 0;
    }

    size_t Connection::send(const char *message, std::size_t len) {
        return 0;
    }

    bool Connection::connect(const char* ip_address, const char* port) {
        //	auto self(shared_from_this());

        LOG_INF(_KV_(ip_address,port));
        tcp::resolver::query query(ip_address, port); 
        auto endpoint_iterator = resolver_.resolve(query);
        boost::asio::async_connect(socket_,
                endpoint_iterator,
                [this](const boost::system::error_code& error, const tcp::resolver::iterator&){
                        std::cout<<"lianjieshang le serverle"<<std::endl;
                        if(!error){
                                LOG_INF(_KV_("message","Connected to server[")

                                      //  <<ip_address<<":"<<port<<"]"

                                        );

                        }else{
                                LOG_INF(_KV_("message","Connected faild to server[")

                                       // <<ip_address<<":"<<port<<"]"

                                        );					}
        }
        );
       

        //tcp::resolver::query query(ip_address, port);
       // auto endpoint_iterator = resolver_.resolve(query);
       // boost::system::error_code error;
       // socket_.connect(tcp::endpoint(ip::address::from_string("192.168.1.61"), 9890),error);
        
       // if (!error) {
       //     LOG_INF(_KV_("message", "Connected to server["));
       // } else {
        //    LOG_INF(_KV_("message", "Connected faild to server["));
        //}
        //boost::asio::async_connect(socket_,
        //	endpoint_iterator,
        //	boost::bind(&Connection::connect_handler,this,
        //	boost::asio::placeholders::error,endpoint_iterator));

        /*
        socket_.async_connect(tcp::endpoint(ip::address::from_string("192.168.1.61"), 9890),
             [this](boost::system::error_code ec, tcp::resolver::iterator)
        {
          if (!ec)
          {
            //do_read_header();
          }
        }
               );
*/
        return 0;
    }

    void Connection::init() {

    }


	void Connection::receive(){
	
	}
    void Connection::connect_handler(const boost::system::error_code& error) {
        if (!error) {
            LOG_INF(_KV_("message", "Connected to server["));
        } else {
            LOG_INF(_KV_("message", "Connected faild to server["));
        }
    }

    void Connection::do_read() {
        auto self(shared_from_this());
        // socket_.

    }


}