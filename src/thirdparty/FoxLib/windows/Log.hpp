/* Logs data to log.txt.*/
#pragma once
#include <Windows.h>
#include <cassert>

namespace foxlib {
	struct Log {
		HANDLE logFile;
		//Opens the log file
		bool init() {
			logFile = CreateFile("log.txt",
			                     GENERIC_WRITE,
			                     FILE_SHARE_READ,
			                     nullptr,
			                     CREATE_ALWAYS,
			                     0,
			                     nullptr);
			return logFile != INVALID_HANDLE_VALUE;
		}
		void flush() {
			BOOL worked = FlushFileBuffers(logFile);
			assert(worked);
		}
		//Closes the log file
		void cleanup() {
			CloseHandle(logFile);
		}
		void write(char const* msg, uintptr len) {
			if (logFile != nullptr) {
				DWORD bytesWritten;
				WriteFile(logFile,
				          msg,
				          len,
				          &bytesWritten,
				          nullptr);
			}
			flush();
		}		
		void write(char const* cStr) {
			write(cStr, strlen(cStr));
		}
		//TODO: support for numbers
	} log;
}
