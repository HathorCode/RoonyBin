#include <Windows.h>

#include "engine/log.hpp"
#include "engine/opengl.hpp"
#include "engine/platform.hpp"

#include "FoxLib/FoxLib.hpp"

void gameLoop() {
  // Handle game time here

}

int WINAPI WinMain(HINSTANCE paramHInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
  // eventually change these values
  const uint8 WIDTH = 720;
  const uint8 HEIGHT = 480;

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

  gl.init();
  gameLoop();

  //Should never be called
  ExitProgram();
  return 0;
}
