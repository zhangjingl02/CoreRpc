#include <iostream>

#include "protobuf_decoder.h"
#include "rpc.pb.h"
#include "../net/net_def.h"
namespace rpc{
	int ProtobufDecoder::decode(const net::TcpConnection& connection, net::NetBuffer& buffer){
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
					std::cout<<"read rpc buffer success!"<<std::endl;
					boost::shared_ptr<TransferMessage> messagePtr(new TransferMessage());
				
					if(messagePtr->ParseFromArray(buffer.readStream(len),len)){
						dispatcher_->pushMessage(messagePtr);
					}
					
				}
			}
			
		}
		return 0;
	}
}