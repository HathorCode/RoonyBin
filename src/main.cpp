#include <Windows.h>
#include <windowsx.h>

#include "engine\log.hpp"
#include "engine\opengl.hpp"
#include "engine\platform.hpp"
#include "FoxLib\FoxLib.hpp"
#include "engine\touchme.hpp"

#include "engine\renderer\texture.hpp"
#include "engine\renderer\renderer.hpp"


namespace rb {
  void gameLoop() {
    // Handle game time here
    while(true) {
      win.handleInput();
			renderer.init();
			// start rendering based on a clocked time
	  	//int test = (int)texture.loadTexture("lock.png");

    }
  }
}

int WINAPI WinMain(HINSTANCE paramHInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {

  using namespace rb;
  rb::log.init();

  hInstance = paramHInstance;
  win.registerWindowClass();

  if(!win.init()) {
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

  gl.init();
  gameLoop();

  //Should never be called
  ExitProgram();
  return 0;
}
