#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "../log.hpp"
#include "../opengl.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "FoxLib/FoxLib.hpp"

namespace rb {
  /* Proper shader usage: load the shaders, and then init them, which activates them */
  struct Shader {
    GLuint shaderID;

    /* Activates the previously linked shader program */
    Shader& init() {
      glUseProgram(shaderID);
      return *this; //this sucks ik ik
    }

    /* Loads a vertex and fragment shader, and compiles them into a shader program */
    void compile(const char* vertexSource, const char* fragmentSource) {
		GLuint sVertex, sFragment;
		// Vertex Shader
		sVertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(sVertex, 1, &vertexSource, NULL);
		glCompileShader(sVertex);
		// Fragment Shader
		sFragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(sFragment, 1, &fragmentSource, NULL);
		glCompileShader(sFragment);
		// If geometry shader source code is given, also compile geometry shader
		// Shader Program
		shaderID = glCreateProgram();
		glAttachShader(shaderID, sVertex);
		glAttachShader(shaderID, sFragment);
		glLinkProgram(shaderID);
		// Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(sVertex);
		glDeleteShader(sFragment);
    }

    // helper funcs I found online that will be used for transformations
	void setFloat(const GLchar *name, GLfloat value, GLboolean useShader = false){
      if (useShader){
        init();
      }
      glUniform1f(glGetUniformLocation(shaderID, name), value);
    }

    void setInteger(const GLchar *name, GLint value, GLboolean useShader = false) {
      if (useShader){
        init();
      }
	  int debug = glGetUniformLocation(shaderID, name);
      glUniform1i(glGetUniformLocation(shaderID, name), value);
    }

    void setVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false){
      if (useShader){
        init();
      }
      glUniform2f(glGetUniformLocation(shaderID, name), x, y);
    }

	void setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false){
      if (useShader){
        init();
      }
      glUniform2f(glGetUniformLocation(shaderID, name), value.x, value.y);
    }

	void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false){
      if (useShader){
        init();
      }
      glUniform3f(glGetUniformLocation(shaderID, name), x, y, z);
    }

	void setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false){
      if (useShader){
        init();
      }
      glUniform3f(glGetUniformLocation(shaderID, name), value.x, value.y, value.z);
    }

	void setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false) {
      if (useShader){
        init();
      }
      glUniform4f(glGetUniformLocation(shaderID, name), x, y, z, w);
    }

	void setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false) {
      if (useShader){
        init();
      }
      glUniform4f(glGetUniformLocation(shaderID, name), value.x, value.y, value.z, value.w);
    }

	void setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false){
      if (useShader){
        init();
      }
	  int debug = glGetUniformLocation(shaderID, name);
      glUniformMatrix4fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }
  };
}