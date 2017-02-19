#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "..\opengl.hpp"
#include "texture.hpp"
#include "shader.hpp"

namespace rb {
  struct Sprite {
    Shader shader;
    GLuint quadVAO;

    void init(Shader &shaderParam) {
      shader = shaderParam;
      initRenderData();
    }

    void drawSprite(Texture &tex, glm::vec2 pos, glm::vec2 size, GLfloat rotate, glm::vec3 color) {
      //shader.use();
      glm::mat4 model;

      // Order of sprite modifications:
      // scale, rotation, translation in reverse
      model = glm::translate(model, glm::vec3(pos, 0.0f));

      //edit scaling factors as needed, shouldn't need them at first
      model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
      model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
      model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5 * size.y, 0.0f));

      // final scaling
      model = glm::scale(model, glm::vec3(size, 1.0f));

      shader.setMatrix4("model", model, false);
      shader.setVector3f("spriteColor", color, false);

      glActiveTexture(GL_TEXTURE0);
      tex.bind();

      glBindVertexArray(quadVAO);
      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

    }

    void initRenderData() {
      GLuint VBO;
      GLfloat vertices[] = {
        // pos     //tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
      };
      // generate stuff
      glGenVertexArrays(1, &quadVAO);
      glGenBuffers(1, &VBO);

      // populate buffer
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
	  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      // set attributes
      glBindVertexArray(quadVAO);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4* sizeof(GLfloat), (GLvoid*)0);

      //free buffers
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    }

  };
}
