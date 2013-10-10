#ifndef _H_COMMON_RPC_PROTOBUF_ENCODER_H
#define _H_COMMON_RPC_PROTOBUF_ENCODER_H
#include <google/protobuf/message.h>
#include <google/protobuf/io/coded_stream.h>
#include "../net/message_encoder.h"
namespace rpc{

	class ProtobufEncoder :public net::MessageEncoder{
	public:
		buffer::shared_buffer&  encode(void* message){
			
			google::protobuf::Message* message_p=(google::protobuf::Message*)message;
			buffer::shared_buffer buffer(5+message_p->ByteSize());
			buffer::uint8* stream=new buffer::uint8[(5+message_p->ByteSize())];
			google::protobuf::io::ArrayOutputStream s;
			return buffer;
		}
	};
	

}
#endif