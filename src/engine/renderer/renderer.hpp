#pragma once

#include "engine/log.hpp"
#include "engine/opengl.hpp"
#include "shader.hpp"
#include "sprite.hpp"
#include "assetmanager.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "src/game/level.hpp"

namespace rb {
  /*Srsly wtf am I gonna doooooo */
  struct Renderer {
    Shader mainShader;
    Sprite *rendered;
	std::vector<Level> levels;
	uint8 levelNum;

    // could be named render, doesn't really matter
    void update() {
      glClear(GL_COLOR_BUFFER_BIT);
      rendered->drawSprite(manager.Textures["grass"], glm::vec2(200, 200), glm::vec2(250, 250), 45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
      //simply draws triangle for now
    }
    void init() {
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      manager.loadShader("shaders/default.vs", "shaders/default.fs", "sprite");

	  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(win.WIDTH), static_cast<GLfloat>(win.HEIGHT),
								0.0f, -1.0f, 1.0f);
	  Shader spriteShader = manager.Shaders["sprite"];
	  spriteShader.init();
	  spriteShader.setInteger("image", 0);
	  spriteShader.setMatrix4("projection", projection);

      //load textures, probably doesn't work on my computer
      manager.loadTexture("res/1.png", GL_TRUE, "grass");
	  rendered = new Sprite; 
	  (*rendered).init(spriteShader);
    }

  } renderer;

}
