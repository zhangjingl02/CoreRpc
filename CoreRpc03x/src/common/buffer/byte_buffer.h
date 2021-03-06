#ifndef _H_BUFFER_BYTE_BUFFER_H
#define _H_BUFFER_BYTE_BUFFER_H
#include <boost/shared_array.hpp>
#include <boost/circular_buffer.hpp>
#include "buffer_def.h"
namespace buffer{
	class  ByteBuffer{
	public:
		const static int kDefaultSize=1024*10;
	public:

		ByteBuffer();
		explicit ByteBuffer(uint32 size);
		template <typename POD_TYPE, uint32 N>
		explicit ByteBuffer(POD_TYPE (&buffer)[N]);
		template <typename POD_TYPE>
		ByteBuffer(POD_TYPE* buffer, uint32 size);
		explicit ByteBuffer(const_buffer& buffer);
		explicit ByteBuffer(mutable_buffer& buffer);
		virtual ~ByteBuffer();
		ByteBuffer& markReaderIndex();
		ByteBuffer& restore();
		ByteBuffer& resize(uint32 size);
		ByteBuffer& append(char* data,size_t size);
		uint8* bytes();
		const uint8* bytes() const;
		uint32 size() const;
		bool empty() const;
		uint32 capacity() const;


	private:
		boost::shared_array<uint8> buffer_;
		boost::circular_buffer<uint8> buffer2;
		size_t readerIndex_;
		size_t writerIndex_;
		size_t markReaderIndex_;
		size_t capacity_;
		size_t real_capacity_;
	};


}
#endif