#pragma once

#include "../log.hpp"
#include "../opengl.hpp"
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
	  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	  glClear(GL_COLOR_BUFFER_BIT);
      rendered->drawSprite(AssetManager::Textures["grass"], glm::vec2(50, 50), glm::vec2(250, 250), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
      //simply draws triangle for now
    }
    void init() {
	  glViewport(0, 0, win.WIDTH, win.HEIGHT);
	  glEnable(GL_CULL_FACE);
	  glEnable(GL_BLEND);
	  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//Only consider source alpha level

	  AssetManager::loadShader("shaders/sprite.vs", "shaders/sprite.fs", "sprite");

	  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(win.WIDTH), static_cast<GLfloat>(win.HEIGHT),
								0.0f, -1.0f, 1.0f);

	  ((AssetManager::Shaders["sprite"]).init()).setInteger("image", 0);
	  (AssetManager::Shaders["sprite"]).setMatrix4("projection", projection);

      //load textures, probably doesn't work on my computer
	  AssetManager::loadTexture("res/1.png", GL_TRUE, "grass");
	  rendered = new Sprite;
	  rendered->init(AssetManager::Shaders["sprite"]);
    }

  } renderer;

}
