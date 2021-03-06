#include <iostream>

#include "protobuf_decoder.h"
#include "rpc.pb.h"
#include "../net/net_def.h"
namespace rpc{
	
	int protobuf_decoder::decode(net::tcp_connection& connection, net::NetBuffer& buffer){
		buffer.markReaderIndex();
		google::protobuf::uint8 buf[5]={'\0','\0','\0','\0','\0'};
		for(int i=0;i<5;i++){
			if(!buffer.isReadable()){
				buffer.resetReaderIndex();
				return net::NEED_DATA;
			}
			buf[i]=buffer.readInt8();
			if(buf[i]>0){
					google::protobuf::io::CodedInputStream istream(buf,5);
				google::protobuf::uint32 len;
				istream.ReadVarint32(&len);
				if(buffer.readableBytes()>=len){
					std::cout<<"read rpc buffer success!"<<len<<std::endl;
					boost::shared_ptr<TransferMessage> messagePtr(new TransferMessage());
				
					if(messagePtr->ParseFromArray(buffer.readStream(len),len)){
						dispatcher_->pushMessage(connection,messagePtr);
					}else{
						std::cout<<"read rpc buffer success! but parse failed:"<<len<<std::endl;
					}
					
				}
			}
			
		}
		return net::RECV_SUCCESS;
	}
	/*
	int ProtobufDecoder::decode(net::TcpConnection& connection, buffer::shared_buffer& buffer,std::size_t size){
	
		boost::shared_ptr<TransferMessage> messagePtr(new TransferMessage());
				
		if(messagePtr->ParseFromArray(buffer.bytes(),buffer.size())){
						dispatcher_->pushMessage(connection,messagePtr);
					}
		return 0;
	}

	std::size_t ProtobufDecoder::frameDecode(net::TcpConnection& connection, buffer::shared_buffer& buffer,std::size_t size){
		buffer.remove(size);
		if(buffer.empty()){
			buffer.restore();
			google::protobuf::io::CodedInputStream istream(buffer.bytes(),5);
				google::protobuf::uint32 len;
				istream.ReadVarint32(&len);
				return len;
		}
		return 0;
	
	}
	*/


}