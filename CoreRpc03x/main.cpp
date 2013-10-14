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
#include "src/common/rpc/rpc_service_skeleton.h"
#include "src/common/net/message_dispatcher.h"
#include "ismp.pb.h"
#include "src/common/rpc/protobuf_decoder.h"
#include "src/common/buffer/shared_buffer.h"
#include "src/common/buffer/shared_buffer_list.h"
#include "src/common/rpc/protobuf_encoder.h"
using namespace std;



/*
 * 
 */
int main(int argc, char** argv) {

	google::InitGoogleLogging(argv[0]);  
google::LogToStderr();//只输出到标准错误输出
LOG(INFO) <<"my first info";   int valueint=10;  
LOG_IF(ERROR, valueint=10)<<" valueint=10";
unsigned int a=2;
buffer::shared_buffer buffer1();

buffer::shared_buffer_list list;
	boost::asio::io_service io;
	net::MessageDispatcher<TransferMessage> dispatcher;
	rpc::RpcServiceSkeleton sk(&dispatcher);
	rpc::ProtobufDecoder decoder(&dispatcher);
	rpc::ProtobufEncoder encoder;
	net::TcpServer server(3);
	server.decoder(&decoder);
	server.encoder(&encoder);
	sk.start();
	server.start(9997);
	io.run();
 
	cin.get();
    return 0;
}

