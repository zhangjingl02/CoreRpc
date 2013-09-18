/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2013年9月17日, 下午1:09
 */
#ifdef WIN32
#define GLOG_NO_ABBREVIATED_SEVERITIES
#endif
#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include "src/common/net/net_buffer.h"
#include "src/common/net/connection.h"

#include <glog/logging.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
google::InitGoogleLogging(argv[0]);  
google::LogToStderr();//只输出到标准错误输出
LOG(INFO) <<"my first info";   int valueint=10;  
LOG_IF(ERROR, valueint=10)<<" valueint=10";
boost::asio::io_service io;

	net::Connection con(io);
	con.connect("192.168.2.129","9020");
	net::NetBuffer buffer;

	buffer.appendInt32((int32_t)65);
	buffer.appendInt32((int32_t)-98);
	buffer.append("this is a test",sizeof "this is a test");

	int32_t a=buffer.readInt32();
	int32_t b=buffer.readInt32();
	//int32_t c=buffer.readInt32();
	//string str;
	string str=buffer.readString(sizeof "this is a test");
	cout << "Hello world"<<a<<"|"<<b<<""<<str.c_str()<<endl;
	 auto func = [] () { cout << "Hello world"<<endl; };  
    func(); // now call the functionaa
	 cin.get();
    return 0;
}

