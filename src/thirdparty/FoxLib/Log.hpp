/*Logs data to log.txt.*/
#pragma once
#include "Types.hpp"
#ifdef _WIN32
#	include "windows/Log.hpp"
#else
#	error Unsupported platform for log.hpp
#endif
