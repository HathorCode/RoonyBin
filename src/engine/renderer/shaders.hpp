#pragma once

#include "engine\log.hpp"
#include "engine\opengl.hpp"
#include "engine\io.hpp"

#include "FoxLib\FoxLib.hpp"

namespace rb {
  /* Proper shader usage: load the shaders, and then init them, which activates them */
  struct Shader {
    GLuint shaderID;

    /* Activates the previously linked shader program */
    void init() {
      glUseProgram(shaderID);
    }

    /* Loads a vertex and fragment shader, and compiles them into a shader program */
    GLuint loadShaders(const char* vertexFileName, const char* fragmentFileName) {
      GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

      char* vertexShaderSource = io.loadFromFile(vertexFileName);
      glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
      glCompileShader(vertexShader);

      // Error checking can be changed to get length of error string
      GLint success;
      GLchar errorLog[512];
      glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
      if(!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, errorLog);
        log.write(errorLog);
        log.write("\n");
      }

      GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      char* fragmentShaderSource = io.loadFromFile(vertexFileName);
      glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
      glCompileShader(fragmentShader);

      // Links the two Shaders
      GLuint shaderProgram;
      shaderProgram = glCreateProgram();
      glAttachShader(shaderProgram, vertexShader);
      glAttachShader(shaderProgram, fragmentShader);
      glLinkProgram(shaderProgram);

      //More error checking
      glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
      if(!success){
        glGetProgramInfoLog(shaderProgram, 521, nullptr, errorLog);
        log.write(errorLog);
        log.write("\n");
      }

      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);
      this->shaderID = shaderProgram;
      return shaderProgram;
    }
  };
}
