#include <Windows.h>

#include "engine\log.hpp"
#include "engine\opengl.hpp"
#include "engine\platform.hpp"
#include "FoxLib\FoxLib.hpp"
#include "engine\touchme.hpp"

namespace rb {
  void gameLoop() {
    // Handle game time here
    while(true) {
      win.handleInput();
      //rendering eventually goes here
      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
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
