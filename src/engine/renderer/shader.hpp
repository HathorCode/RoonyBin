#pragma once

#include "engine\log.hpp"
#include "engine\opengl.hpp"
#include "engine\io.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "FoxLib\FoxLib.hpp"

namespace rb {
  /* Proper shader usage: load the shaders, and then init them, which activates them */
  struct Shader {
    GLuint shaderID;

    /* Activates the previously linked shader program */
    Shader init() {
      glUseProgram(shaderID);
      return *this; //this sucks ik ik
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
      shaderID = glCreateProgram();
      glAttachShader(shaderID, vertexShader);
      glAttachShader(shaderID, fragmentShader);
      glLinkProgram(shaderID);

      //More error checking
      glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
      if(!success){
        glGetProgramInfoLog(shaderID, 521, nullptr, errorLog);
        log.write(errorLog);
        log.write("\n");
      }

      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);
      return shaderID;
    }

    // helper funcs I found online that will be used for transformations
    void setFloat(const GLchar *name, GLfloat value, GLboolean useShader){
      if (useShader){
        init();
      }
      glUniform1f(glGetUniformLocation(shaderID, name), value);
    }

    void setInteger(const GLchar *name, GLint value, GLboolean useShader) {
      if (useShader){
        init();
      }
      glUniform1i(glGetUniformLocation(shaderID, name), value);
    }

    void setVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader){
      if (useShader){
        init();
      }
      glUniform2f(glGetUniformLocation(shaderID, name), x, y);
    }

    void setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader){
      if (useShader){
        init();
      }
      glUniform2f(glGetUniformLocation(shaderID, name), value.x, value.y);
    }

    void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader){
      if (useShader){
        init();
      }
      glUniform3f(glGetUniformLocation(shaderID, name), x, y, z);
    }

    void setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader){
      if (useShader){
        init();
      }
      glUniform3f(glGetUniformLocation(shaderID, name), value.x, value.y, value.z);
    }

    void setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader) {
      if (useShader){
        init();
      }
      glUniform4f(glGetUniformLocation(shaderID, name), x, y, z, w);
    }

    void setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader) {
      if (useShader){
        init();
      }
      glUniform4f(glGetUniformLocation(shaderID, name), value.x, value.y, value.z, value.w);
    }

    void setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader){
      if (useShader){
        init();
      }
      glUniformMatrix4fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

  };
}
