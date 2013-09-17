#ifndef _NET_NET_BUFFER_H
#define _NET_NET_BUFFER_H
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <assert.h>
#include <string>
namespace net{
	class NetBuffer{
	public:
		static const std::size_t kCheapPrepend = 8;
		static const std::size_t kInitialSize = 1024;
		NetBuffer()
			:buffer_(kCheapPrepend + kInitialSize),
			readerIndex_(kCheapPrepend),
			writerIndex_(kCheapPrepend),
			markReaderIndex_(0)
		{
			assert(readableBytes() == 0);
			assert(writableBytes() == kInitialSize);

		}
	public:
		void markReaderIndex(){markReaderIndex_=readerIndex_;} ;
		void resetReaderIndex(){readerIndex_=markReaderIndex_;} ;
		std::size_t readableBytes()const{return writerIndex_-readerIndex_;} ;
		std::size_t writableBytes()const{return buffer_.size()-writerIndex_;};
		bool readBytes(char* message,std::size_t len);
		const char* peek() const {return begin()+readerIndex_;};
		int8_t peekInt8() const{
			assert(readableBytes() >= sizeof(int8_t));
			int8_t x = *peek();
			return x;
		}

		int16_t peekInt16() const{
			assert(readableBytes() >= sizeof(int16_t));
			int16_t x16=0;
			memcpy(&x16,peek(),sizeof x16);
		};
		int32_t peekInt32() const{
			assert(readableBytes() >= sizeof(int32_t));
			int32_t x32=0;
			memcpy(&x32,peek(),sizeof x32);
		};

		int64_t peekInt64() const{
			assert(readableBytes() >= sizeof(int64_t));
			int64_t x64=0;
			memcpy(&x64,peek(),sizeof x64);
		};

		void peekString(std::string& str,size_t len)const {
			assert(readableBytes() >= len);
			//memcpy(str.begin(),peek(),len);
		};

		int8_t readInt8(){
			int8_t result=peekInt8();
			retrieve(sizeof(int8_t));
			return result;
		}

		int16_t readInt16(){
			int16_t result=peekInt16();
			retrieve(sizeof(int16_t));
			return result;
		}

		int32_t readInt32(){
			int32_t result=peekInt32();
			retrieve(sizeof(int32_t));
			return result;
		}


		void readString(std::string &str,size_t len){
			peekString(str,len);
			retrieve(len);
		}
		void retrieve(size_t len)
		{
			assert(len <= readableBytes());
			if (len < readableBytes())
			{
				readerIndex_ += len;
			}
			else
			{
				retrieveAll();
			}
		}
		void retrieveAll()
		{
			readerIndex_ = kCheapPrepend;
			writerIndex_ = kCheapPrepend;
		}

		void prepend(const void* /*restrict*/ data, size_t len)
		{
			assert(len <= prependableBytes());
			readerIndex_ -= len;
			const char* d = static_cast<const char*>(data);
			std::copy(d, d+len, begin()+readerIndex_);
		}
	private:

		char* begin(){ return &*buffer_.begin();};
		const char* begin() const { return &*buffer_.begin(); }
		std::size_t markReaderIndex_;
		std::vector<char> buffer_;
		std::size_t readerIndex_;
		std::size_t writerIndex_;
	};
}
#endif