#include <iostream>

#include "protobuf_decoder.h"
#include "rpc.pb.h"
#include "../net/net_
namespace rpc{
	int ProtobufDecoder::decode(const net::TcpConnection& connection, net::NetBuffer& buffer){
		buffer.markReaderIndex();
		google::protobuf::uint8 buf[5]={'\0','\0','\0','\0','\0'};
		for(int i=0;i<5;i++){
			if(!buffer.isReadable()){
				buffer.resetReaderIndex();
				return NEED_DATA;
			}
			buf[i]=buffer.readInt8();
			if(buf[i]>0){
					google::protobuf::io::CodedInputStream istream(buf,5);
				google::protobuf::uint32 len;
				istream.ReadVarint32(&len);
				if(buffer.readableBytes()>=len){
					std::cout<<"read rpc buffer success!"<<std::endl;

					TransferMessage tm;
					tm.ParseFromArray(buffer.readStream(len),len);
					std::cout<<"command:"<<tm.command()<<std::endl;

					if(tm.command()==::TransferMessage_Command_Login){
						Login login;
						login.ParseFromString(tm.message());

						std::cout<<"pwd:"<<login.password()<<"|user:"<<login.username()<<std::endl;
					}
				}
			}

		




		}



	}
}