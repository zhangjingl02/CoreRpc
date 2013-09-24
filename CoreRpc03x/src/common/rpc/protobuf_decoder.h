#ifndef _H_RPC_PROTOBUF_DECODER_H
#define _H_RPC_PROTOBUF_DECODER_H
#include <google/protobuf/message.h>
#include <google/protobuf/io/coded_stream.h>
#include "../net/tcp_connection.h"
#include "../net/message_decoder.h"
#include "../net/net_buffer.h"
namespace rpc{
	class ProtobufDecoder: public net::MessageDecoder
	{
		public:
			ProtobufDecoder(){}
		public :
			void decode(const net::TcpConnection& connection, net::NetBuffer& buffer);
		private:

	};
}
#endif