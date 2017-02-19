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
	int sysID;
	int pointX;
	int pointY;
};

circle circlesArray[MAXPOINTS];
int touchCount = 0;
int cycleCount = 0;

namespace rb {

	struct TouchEng {

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
					return i;
				}
			}
			// Out of contacts
			return -1;
		}
		void releaseTouch(int dwID) {
			for (int i = 0; i < MAXPOINTS; i++) {
				if (circlesArray[i].sysID == dwID) {
					circlesArray[i].sysID = -1;
					circlesArray[i].pointX = -1;
					circlesArray[i].pointY = -1;
				}
			}
			stopMoving();
		}

		bool touchCheck() {
			// tests for touch capability
			int value = GetSystemMetrics(SM_DIGITIZER);
			if (value  & NID_MULTI_INPUT) {
				return true;
			} else { return false; }
		}

		void handleJoystick(long x, long y) {
			//TODO: put joystick center coordinates here
			int xCoord = 32;
			int yCoord = 32;
			
			bool up = y < yCoord;
			bool down = y > yCoord;
			bool left = x < xCoord;
			bool right = x > xCoord;
			if (up) {
				gameControls.up = true;
			} else {
				gameControls.up = false;
			}
			if (down) {
				gameControls.down = true;
			} else {
				gameControls.down = false;
			}
			if (left) {
				gameControls.left = true;
			} else {
				gameControls.left = false;
			}
			if (right) {
				gameControls.right = true;
			} else {
				gameControls.right = false;
			}
		}

		void stopMoving() {
			gameControls.up = false;
			gameControls.down = false;
			gameControls.left = false;
			gameControls.right = false;
		}

	

	} touch;
}