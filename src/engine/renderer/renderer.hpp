#pragma once

#include "engine\log.hpp"
#include "engine\opengl.hpp"
#include "engine\renderer\shader.hpp"

namespace rb {
  /*Srsly wtf am I gonna doooooo */
struct Renderer {
  Shader mainShader;

  void update() {
	  glClear(GL_COLOR_BUFFER_BIT);
    //simply draws triangle for now
  }
  void init() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    mainShader.loadShaders("shaders/default.vs", "shaders/default.fs");
    mainShader.init();
  }
} renderer;

}
