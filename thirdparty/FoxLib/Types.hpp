//Simple typedefs for fixed size things
#pragma once
#include <cstdint>

typedef std::int8_t int8;
typedef std::int16_t int16;
typedef std::int32_t int32;
typedef std::int64_t int64;
typedef std::int_fast32_t fint; //fox int

typedef std::uint8_t uint8;
typedef std::uint16_t uint16;
typedef std::uint32_t uint32;
typedef std::uint64_t uint64;
typedef std::uint_fast32_t fuint; //fox uint

typedef float float32;
typedef double float64;
#ifdef foxLib64
	typedef int64 intptr;
	typedef uint64 uintptr;
#else
	typedef int32 intptr;
	typedef uint32 uintptr;
#endif
