#ifndef _H_BUFFER_BUFFER_DEF_H
#define _H_BUFFER_BUFFER_DEF_H
#pragma once
#include <boost/cstdint.hpp>
#include <boost/chrono.hpp>
#include <boost/asio/buffer.hpp>
namespace buffer{
typedef boost::int8_t	int8;
typedef boost::int16_t	int16;
typedef boost::int32_t	int32;
typedef boost::int64_t	int64;
typedef boost::uint8_t	uint8;
typedef boost::uint16_t	uint16;
typedef boost::uint32_t	uint32;
typedef boost::uint64_t	uint64;
typedef boost::chrono::high_resolution_clock clock;
typedef clock::duration duration;
typedef boost::asio::mutable_buffer mutable_buffer;
typedef boost::asio::const_buffer const_buffer;
using boost::asio::buffer;
using boost::asio::buffer_cast;
using boost::asio::buffer_size;
}
#endif