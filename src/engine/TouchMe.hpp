#pragma once

#include <Windows.h>
#include "log.hpp"
#include "platform.hpp"
#include "FoxLib\FoxLib.hpp"
#include "windows.hpp"

namespace rb {

	struct TouchEng {

		bool touchCheck() {
			// test for touch
			int value = GetSystemMetrics(SM_DIGITIZER);
			if (value  & NID_MULTI_INPUT) {
				/* digitizer is multitouch */
				return true;
			} else { return false; }
		}


	} touch;
}