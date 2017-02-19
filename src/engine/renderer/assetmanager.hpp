#pragma once

//#include "renderer.hpp"
#include "shaders.hpp"
#include "texture.hpp"

#include <string>
#include <map>

namespace rb {
  /*If you abbreviate this, it becomes assman hehehehehehehehe*/
  struct AssetManager {
    std::map<std::string, Texture> Textures;
    //eventually I want to manage shaders here too, but thats later
    //std::map<std::string, Shader> Shaders;

    Texture loadTextureFromFile(const char* fileName, bool alpha) {
      Texture tex;
      if(alpha) {
        // we defaulted to RGB, so we change it here otherwise
        tex.textureFormat = GL_RGBA;
        tex.imageFormat = GL_RGBA;
      }

      unsigned int width, height;
      unsigned char* imageData = SOIL_load_image(fileName, (int*)&width, (int*)&height, 0,
      tex.imageFormat = GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

      tex.generate(width, height, imageData);
      SOIL_free_image_data(imageData); //we've already used this data
      return tex;
    }

    // finally all of this abstraction leads to smthing
    //also always use loadTexture and NOT loadTextureFromFile
    Texture loadTexture(const char* fileName, bool alpha, std::string name) {
      Textures[name] = loadTextureFromFile(fileName, alpha);
      return Textures[name];
    }

    void clear() {
      //clear shaders too when i use them here
      /*
      for(auto iterateShaders : Shaders) {
        glDeleteProgram(iterateShaders.second.shaderID);
      }
      */
      for(auto iterate : Textures) {
        glDeleteTextures(1, &iterate.second.textureID);
      }
    }

  }
}