#pragma once

#include <glm/glm.hpp>
#include "src/engine/opengl.hpp"
#include "src/engine/renderer/texture.hpp"
#include "src/engine/renderer/sprite.hpp"

namespace rb {
  struct Object {
    glm::vec2 pos, size, vel;
    glm::vec3 color;
    GLfloat rot;
    // this is where i would add code to interact with an object based on
    // an object state

    Texture spriteImg;

    void init(glm::vec2 positionParam, glm::vec2 sizeParam, Texture spriteParam, glm::vec3 colorParam, glm::vec2 velocityParam = glm::vec2(0,0)) {
      pos =positionParam;
      size = sizeParam;
      vel = velocityParam;
	  spriteImg = spriteParam;
      color = colorParam;
      rot = 0.0f;
    }
	/*
	void init() {
		pos = glm::vec2(0, 0);
		size = glm::vec2(1, 1);
		vel = glm::vec2(0, 0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		rot = 0.0f;
		spriteImg = nullptr;
	}
	*/
    void draw(Sprite &renderer) {
      renderer.drawSprite(spriteImg, pos, size, rot, color);
    }
  };
}
