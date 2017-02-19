#pragma once

#include "log.hpp"
#include "platform.hpp"
#include <Windows.h>
#include <windowsx.h>
#include "FoxLib/FoxLib.hpp"
#include "windows.hpp"
#include "../game/controls.hpp"

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
int WIDTH;
int HEIGHT;
int joyX;
int joyY;

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
					if (((joyY - 175) < circlesArray[i].pointY < (joyY + 175)) && ((joyX - 175) < circlesArray[i].pointX < (joyX + 175))) {
						stopMoving();
					}
					circlesArray[i].sysID = -1;
					circlesArray[i].pointX = -1;
					circlesArray[i].pointY = -1;
				}
			}
		}

		void touchInit(int wid, int hei) {
			for (int i = 0; i < MAXPOINTS; i++) {
				circlesArray[i].sysID = -1;
				circlesArray[i].pointX = -1;
				circlesArray[i].pointY = -1;
			}
			WIDTH = wid;
			HEIGHT = hei;
			joyX = WIDTH / 4;
			joyY = 2 * (HEIGHT / 3);
		}

		bool touchCheck() {
			// tests for touch capability
			int value = GetSystemMetrics(SM_DIGITIZER);
			if (value  & NID_MULTI_INPUT) {
				return true;
			} else { return false; }
		}

		void handleJoystick(long x, long y) {
			//might need to change values based on joystick size
			bool up = ((joyY - 150) < y) && (y < joyY);
			bool down = ((joyY + 150) > y) && (y > joyY);
			bool left = ((joyX - 150) < x) && (x < joyX);
			bool right = ((joyX + 150) > x) && (x > joyX);
			if (up && (left || right)) {
				gameControls.up = true;
				log.write("In Joystick range Up \n");
			} else {
				gameControls.up = false;
			}
			if (down && (left || right)) {
				gameControls.down = true;
				log.write("In Joystick range Down \n");
			} else {
				gameControls.down = false;
			}
			if (left && (up || down)) {
				gameControls.left = true;
			} else {
				gameControls.left = false;
			}
			if (right && (up || down)) {
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