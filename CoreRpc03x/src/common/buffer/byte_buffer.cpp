#include "byte_buffer.h"


namespace buffer{

	ByteBuffer::ByteBuffer()
		:readerIndex_(0)
		,writerIndex_(0)
		,markReaderIndex_(0)
		,buffer_(new uint8[kDefaultSize])
		,capacity_(kDefaultSize)
		,real_capacity_(kDefaultSize)
	{
	}

	ByteBuffer::ByteBuffer(uint32 size)
		:readerIndex_(0)
		,writerIndex_(0)
		,markReaderIndex_(0)
		,buffer_(new uint8[size])
		,capacity_(size)
		,real_capacity_(size)
	{
	
	}

	ByteBuffer::ByteBuffer(const_buffer& buffer)
		:readerIndex_(0)
		,writerIndex_(buffer_size(buffer))
		,markReaderIndex_(0)
		,buffer_(new uint8[kDefaultSize])
		,capacity_(kDefaultSize)
		,real_capacity_(kDefaultSize)
	{
		memcpy(buffer_.get(), buffer_cast<const uint8*>(buffer), buffer_size(buffer));
	}

	ByteBuffer::ByteBuffer(mutable_buffer& buffer)
		: readerIndex_(0)
		, writerIndex_(buffer_size(buffer))
		,markReaderIndex_(0)
		,buffer_(new uint8[kDefaultSize])
		,capacity_(kDefaultSize)
		,real_capacity_(kDefaultSize)
	{
		memcpy(buffer_.get(), buffer_cast<uint8*>(buffer), buffer_size(buffer));
	}

	ByteBuffer::~ByteBuffer()
	{
		
	}


	ByteBuffer& ByteBuffer::markReaderIndex(){markReaderIndex_=readerIndex_;return *this;}
	ByteBuffer& ByteBuffer::restore(){
		readerIndex_=0;
		writerIndex_=0;
		markReaderIndex_=0;
		return *this;
	}
	ByteBuffer& ByteBuffer::resize(uint32 size){
		if(capacity_>size){
			capacity_=size;
			if(readerIndex_>size){
				readerIndex_=size;
			}
			if(writerIndex_>size){
				writerIndex_=size;
			}
			
		}

		else if(capacity_<size&&real_capacity_>size){
			capacity_=size;
			
		}else if(capacity_<size){
			uint8* buffer=new uint8[size];
			memcpy(buffer,buffer_.get(),capacity_);
			buffer_.reset(buffer);
			capacity_=size;
			real_capacity_=size;
			
		}
		return *this;
	}

	ByteBuffer& ByteBuffer::append(char* data,size_t size){
		if(capacity_-writerIndex_<size){
			if(capacity_>size+this->size()){
				
			}
		}
		memcpy(buffer_.get()+writerIndex_,data,size);
		writerIndex_+=size;
		return *this;
	}


	uint8* ByteBuffer::bytes(){
		return buffer_.get()+readerIndex_;
	}
	const uint8* ByteBuffer::bytes() const{
		return buffer_.get()+readerIndex_;
	}
	uint32 ByteBuffer::size() const{
		return writerIndex_-readerIndex_;
	}
	bool ByteBuffer::empty() const{
		return size()==0;
	}
	uint32 ByteBuffer::capacity() const{
		return capacity_;
	}



}