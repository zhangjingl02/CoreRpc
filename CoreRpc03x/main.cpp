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
using namespace std;

void test(net::MessageDecoder* test,int aa){

}

/*
 * 
 */
int main(int argc, char** argv) {


	boost::circular_buffer<int> cir(5);
	
	boost::shared_array<int> buffer(new int[10]);
	buffer[4]=4;
	buffer[5]=5;
	buffer[6]=6;
	buffer[7]=7;
	buffer[8]=8;
	
	

	cout<<buffer[0]<<"|"<<buffer[1]<<"|"<<buffer[2]<<"|"<<(11%12)<<endl;

	boost::asio::io_service service;
	
	//boost::shared_ptr<void> n(new net::TcpConnection(service));
	
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

