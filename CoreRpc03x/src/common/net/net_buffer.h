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
		static const std::size_t kInitialSize = 1024*5;
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
			return get16(peek());
		};
		int32_t peekInt32() const{
			assert(readableBytes() >= sizeof(int32_t));
			return get32(peek());
		};

		int64_t peekInt64() const{
			assert(readableBytes() >= sizeof(int64_t));
			return get64(peek());
		};

		std::string peekString(size_t len)const {
			assert(readableBytes() >= len);
			std::string result(peek(),len);
			return result;
		};

		int8_t readInt8(){
			int8_t result=peekInt8();
			retrieve(sizeof(int8_t));
			return result;
		}
		const char* readStream(size_t size){
			const char* result=peek();
			retrieve(size);
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


		std::string readString(size_t len){
			std::string result=peekString(len);
			retrieve(len);
			return result;
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

		void append(const char* data,size_t len){
			ensureWritableBytes(len);
			std::copy(data, data+len, buffer_.begin()+writerIndex_);
			hasWritten(len);
		}

		void append(const void* /*restrict*/ data, size_t len)
		{
			append(static_cast<const char*>(data), len);
		}

		void append(const char data){
			ensureWritableBytes(1);
			buffer_[writerIndex_]=data;
			hasWritten(1);
		}

		void appendInt16(int16_t data){
			append(char(data>>8));
			append(char(data));
		}

		void appendInt32(int32_t data){
			append(char(data>>24));
			append(char(data>>16));
			append(char(data>>8));
			append(char(data));
		}

		char* beginWrite()
		{ return begin() + writerIndex_; }

		const char* beginWrite() const
		{ return begin() + writerIndex_; }

		void hasWritten(size_t len)
		{ writerIndex_ += len; }


		size_t prependableBytes() const{return readerIndex_; };

		void ensureWritableBytes(size_t len)
		{
			if (writableBytes() < len)
			{
				makeSpace(len);
			}
			assert(writableBytes() >= len);
		}

		bool isReadable(){
			return (writerIndex_-readerIndex_>0);
		}
	private:

		char* begin(){ return &*buffer_.begin();};
		const char* begin() const { return &*buffer_.begin(); }
	private:
		static inline int16_t get16(const char* buffer){
			int16_t accumulator=buffer[0];
			accumulator = (accumulator << 8) |buffer[1];
			return accumulator;
		}

		static inline int32_t get32(const char* buffer){
			int32_t accumulator=buffer[0];
			accumulator = (accumulator << 8) |buffer[1];
			accumulator = (accumulator << 16) |buffer[2];
			accumulator = (accumulator << 24) |buffer[3];
			return accumulator;
		}

		static inline int64_t get64(const char* buffer){
			int64_t accumulator=buffer[0];
			accumulator = (accumulator << 8) |buffer[1];
			accumulator = (accumulator << 16) |buffer[2];
			accumulator = (accumulator << 24) |buffer[3];

			accumulator = (accumulator << 32) |buffer[4];
			accumulator = (accumulator << 40) |buffer[5];
			accumulator = (accumulator << 48) |buffer[6];
			accumulator = (accumulator << 56) |buffer[7];
			return accumulator;
		}

		void makeSpace(size_t len)
		{
			if (writableBytes() + prependableBytes() < len + kCheapPrepend)
			{
				// FIXME: move readable data
				buffer_.resize(writerIndex_+len);
			}
			else
			{
				// move readable data to the front, make space inside buffer
				assert(kCheapPrepend < readerIndex_);
				size_t readable = readableBytes();
				std::copy(begin()+readerIndex_,
					begin()+writerIndex_,
					buffer_.begin()+kCheapPrepend);
				readerIndex_ = kCheapPrepend;
				writerIndex_ = readerIndex_ + readable;
				assert(readable == readableBytes());
			}
		}


	private:
		std::size_t markReaderIndex_;
		std::vector<char> buffer_;
		std::size_t readerIndex_;
		std::size_t writerIndex_;
	};
}
#endif