/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2013年9月23日, 上午11:32
 */
#ifdef WIN32
#define GLOG_NO_ABBREVIATED_SEVERITIES
#endif
#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include <glog/logging.h>
#include "src/common/net/tcp_connection.h"
#include "src/common/net/Test.h"
#include "src/common/net/tcp_server.h"
#include <boost/shared_array.hpp>
#include <boost/circular_buffer.hpp>
#include "src/common/net/net_buffer.h"
#include "src/common/rpc/rpc.pb.h"
using namespace std;

void test(net::MessageDecoder* test,int aa){

}

/*
 * 
 */
int main(int argc, char** argv) {

    
	TransferMessage tm;
        tm.set_command(TransferMessage_Command_LoginRsp);
       // 3
      
        /*
	tm.set_command(TransferMessage::Command::TransferMessage_Command_Login);
	tm.set_message("this is a test");
	net::NetBuffer buffer;
	char* stream=new char[1024];
	tm.SerializeToArray(stream,tm.ByteSize());
	buffer.append(stream,tm.ByteSize());
	

	TransferMessage tm2;

	tm2.ParseFromArray(buffer.readStream(tm.ByteSize()),tm.ByteSize());
	
		std::cout<<tm2.message()<<endl;
                */
	boost::asio::io_service service;
	
	
	
	//net::TcpConnectionPtr ptr=(net::TcpConnectionPtr)n;
	
	//cout<<rest<<"|======="<<endl;
	google::InitGoogleLogging(argv[0]);  
	google::LogToStderr();//只输出到标准错误输出
	LOG(INFO) <<"my first info";   int valueint=10;  
	LOG_IF(ERROR, valueint=10)<<" valueint=10";
	
	net::TcpServer s(service);
	s.start(9997);
	service.run();
	std::cin.get();
    return 0;
}

