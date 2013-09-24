#include <iostream>

#include "protobuf_decoder.h"
#include "rpc.pb.h"
#include <google/protobuf/io/coded_stream.h>
namespace rpc{
	void ProtobufDecoder::decode(const net::TcpConnection& connection, net::NetBuffer& buffer){
		buffer.markReaderIndex();
		google::protobuf::uint8 buf[5]={'\0','\0','\0','\0','\0'};
		for(int i=0;i<5;i++){
			if(!buffer.isReadable()){
				buffer.resetReaderIndex();
				return;
			}
			buf[i]=buffer.readInt8();
			if(buf[i]>0){

					google::protobuf::io::CodedInputStream istream(buf,5);
					
					
				google::protobuf::uint32 len;
				istream.ReadVarint32(&len);
				
				if(buffer.readableBytes()>=len){
					char* message;
						buffer.readBytes(message,len);
						google::protobuf::io::CodedInputStream bodystream(message,len);
					TransferMessage tm;
					tm.ParseFromCodedStream();
					std::cout<<"read rpc buffer success!"<<std::endl;
				}
			}

		




		}



	}
}