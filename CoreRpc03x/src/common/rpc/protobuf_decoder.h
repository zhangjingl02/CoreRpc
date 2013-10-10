#ifndef _H_RPC_PROTOBUF_DECODER_H
#define _H_RPC_PROTOBUF_DECODER_H
#include <google/protobuf/message.h>
#include <google/protobuf/io/coded_stream.h>
#include "../net/tcp_connection.h"
#include "../net/message_decoder.h"
#include "../net/net_buffer.h"
#include "../net/message_dispatcher.h"
#include "rpc.pb.h"
namespace rpc{
	class ProtobufDecoder: public net::MessageDecoder
	{
		public:
			
			ProtobufDecoder(net::MessageDispatcher<TransferMessage>* dispatcher)
				:dispatcher_(dispatcher){}
		public :
			int decode(net::TcpConnection& connection, net::NetBuffer& buffer);
			// int decode(net::TcpConnection& connection, buffer::shared_buffer& buffer,std::size_t size);
			// std::size_t frameDecode(net::TcpConnection& connection, buffer::shared_buffer& buffer,std::size_t size);
		private:
			net::MessageDispatcher<TransferMessage>* dispatcher_;

	};
}
#endif