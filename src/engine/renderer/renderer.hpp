#pragma once

#include "engine/log.hpp"
#include "engine/opengl.hpp"
#include "engine/renderer/shader.hpp"

namespace rb {
  /*Srsly wtf am I gonna doooooo */
struct Renderer {
  Shader mainShader;

  // could be named render, doesn't really matter
  void update() {
	  glClear(GL_COLOR_BUFFER_BIT);
    //simply draws triangle for now
  }
  void init() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }
} renderer;

}
