#include <Windows.h>
#include <windowsx.h>

#include "yse/yse.hpp"
#include "engine/log.hpp"
#include "engine/opengl.hpp"
#include "engine/platform.hpp"
#include "FoxLib/FoxLib.hpp"
#include "engine/touchme.hpp"

#include "game/game.hpp"

#include "engine/renderer/texture.hpp"
#include "engine/renderer/renderer.hpp"


namespace rb {
	void gameLoop() {
		game.state = game.GAME_ACTIVE;
		renderer.init();
		// Eventually handle game time
		while (game.state == game.GAME_ACTIVE) {
			YSE::System().update();
			win.handleInput();
			renderer.update();
			// start rendering based on a clocked time
		//int test = (int)texture.loadTexture("lock.png");
		}
	}
}

int WINAPI WinMain(HINSTANCE paramHInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
	using namespace rb;
	rb::log.init();

	YSE::System().init();
	hInstance = paramHInstance;
	win.registerWindowClass();

	// Create the window
	if (!win.init()) {
		//change default options
		if (!win.init()) {
			rb::log.write("[Main.cpp] Failed to create basic window.\n");
			ExitProgram();
		}
	}

	/* //Enable this code to check for multitouch support
	if (!touch.touchCheck()) {
		//check for touch compatibility
		rb::log.write("[Main.cpp] MultiTouch not supported");
		ExitProgram();
	}
	*/

	//initialize the opengl context, and go straight into  the game loop
	gl.init();
	gameLoop();

	//Should never be called
	ExitProgram();
	return 0;
}
