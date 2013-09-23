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
#include "src/common/net/Test.h"
#include "src/common/net/tcp_server.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

	net::TcpConnectionPtr ptr;
	net::NetBuffer buffer;
	net::Test t;
	std::string rest=t.decoder(ptr,buffer);
	cout<<rest<<"|======="<<endl;
	google::InitGoogleLogging(argv[0]);  
	google::LogToStderr();//只输出到标准错误输出
	LOG(INFO) <<"my first info";   int valueint=10;  
	LOG_IF(ERROR, valueint=10)<<" valueint=10";
	boost::asio::io_service service;
	net::TcpServer s(service);
	s.start(9997);
	service.run();
	std::cin.get();
    return 0;
}

