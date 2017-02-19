#pragma once

//#include "renderer.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "../opengl.hpp"
#include "../log.hpp"

#include <string>
#include <map>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace rb {
  /*If you abbreviate this, it becomes assman hehehehehehehehe*/
  struct AssetManager {
    static std::map<std::string, Texture> Textures;
    static std::map<std::string, Shader> Shaders;

    // Use this function over the individual shader one
    static Shader loadShader(const char* vertexFileName, const char* fragmentFileName, std::string name) {
	std::map<std::string, Shader> Shaders;
      Shader shaderToReturn = loadShaderFromFile(vertexFileName, fragmentFileName);
      Shaders[name] = shaderToReturn;
      return shaderToReturn;
    }

	static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile) {
		// 1. Retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		try {
			// Open files
			std::ifstream vertexShaderFile(vShaderFile);
			std::ifstream fragmentShaderFile(fShaderFile);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vertexShaderFile.rdbuf();
			fShaderStream << fragmentShaderFile.rdbuf();
			// close file handlers
			vertexShaderFile.close();
			fragmentShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			// If geometry shader path is present, also load a geometry shader
		}
		catch (std::exception e){
			log.write("ERROR::SHADER: Failed to read shader files");
		}
		const GLchar *vShaderCode = vertexCode.c_str();
		const GLchar *fShaderCode = fragmentCode.c_str();
		// 2. Now create shader object from source code
		Shader shader;
		shader.compile(vShaderCode, fShaderCode);
		return shader;
	}

    // finally all of this abstraction leads to smthing
    //also always use loadTexture and NOT loadTextureFromFile
	static Texture loadTexture(const char* fileName, bool alpha, std::string name) {
      Textures[name] = loadTextureFromFile(fileName, alpha);
      return Textures[name];
    }

	static Texture loadTextureFromFile(const char* fileName, bool alpha = true) {

      Texture tex;
      if(alpha) {
        // we defaulted to RGB, so we change it here otherwise
        tex.textureFormat = GL_RGBA8;
        tex.imageFormat = GL_RGBA8;
      }

      int width, height;
      unsigned char* imageData = stbi_load(fileName, &width, &height, 0, 4);

	  if (imageData = nullptr) {
		  log.write("[AssetManager] Couldn't load image data");
	  }
      tex.generate(width, height, imageData);
	  stbi_image_free(imageData); //we've already used this data
      return tex;
    }

	static void clear() {
      for(auto iterateShaders : Shaders) {
        glDeleteProgram(iterateShaders.second.shaderID);
      }

      for(auto iterate : Textures) {
        glDeleteTextures(1, &iterate.second.textureID);
      }
    }

  };
  std::map<std::string, Texture> AssetManager::Textures;
  std::map<std::string, Shader> AssetManager::Shaders;
}
