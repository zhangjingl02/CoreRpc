#ifndef _H_COMMON_RPC_PROTOBUF_ENCODER_H
#define _H_COMMON_RPC_PROTOBUF_ENCODER_H
#include <google/protobuf/message.h>
#include <google/protobuf/io/coded_stream.h>
#include "../net/message_encoder.h"
namespace rpc{

	class protobuf_encoder :public net::message_encoder{
	public:
		bool  encode(void* message,buffer::shared_buffer& buffer){
			
			google::protobuf::Message* message_p=(google::protobuf::Message*)message;
			int bodyLen=message_p->ByteSize();
			int headerLen=google::protobuf::io::CodedOutputStream::VarintSize32(bodyLen);
			buffer.resize(headerLen+bodyLen);
			
			google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(bodyLen,buffer.writeBytes());
			buffer.writed(headerLen);
			if(message_p->SerializeToArray(buffer.writeBytes(),bodyLen)){
				buffer.writed(bodyLen);
				return true;
			}
			
			return false;
		}
	};
	

}
#endif