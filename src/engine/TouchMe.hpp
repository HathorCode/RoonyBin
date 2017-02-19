#pragma once

#include "log.hpp"
#include "platform.hpp"
#include <Windows.h>
#include <windowsx.h>
#include "FoxLib\FoxLib.hpp"
#include "windows.hpp"

#define MAXPOINTS 10

static int radius = 50;
struct circle {
	COLORREF color;
	int sysID;
	int pointX;
	int pointY;
};

circle circlesArray[MAXPOINTS];
int touchCount = 0;
int cycleCount = 0;

namespace rb {

	struct TouchEng {

		// This function makes a random colour value for the test circle
		COLORREF MakeColor() {
			return RGB(rand() % (255), rand() % (255), rand() % (255));
		}

		// This function is used to return an index given an ID
		int GetCircleIndex(int dwID) {
			for (int i = 0; i < MAXPOINTS; i++) {
				if (circlesArray[i].sysID == dwID) {
					return i;
				}
			}
			for (int i = 0; i < MAXPOINTS; i++) {
				if (circlesArray[i].sysID == -1) {
					circlesArray[i].sysID = dwID;
					circlesArray[i].color = MakeColor();
					return i;
				}
			}
			// Out of contacts
			return -1;
		}

		// This function is used to release an array member given an ID
		void ReleaseCircleIndex(int dwID) {
			for (int i = 0; i < MAXPOINTS; i++) {
				if (circlesArray[i].sysID == dwID) {
					circlesArray[i].sysID = -1;
					circlesArray[i].pointX = -1;
					circlesArray[i].pointY = -1;
				}
			}

		}

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