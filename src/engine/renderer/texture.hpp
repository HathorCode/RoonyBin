/*SOIL should only ever touch this file since its directly related to textures*/
#pragma once

#include "soil/SOIL.h"
#include "engine/opengl.hpp"

namespace rb {
  struct Texture {
    GLuint textureIDArr; // eventually an array

    /*Loads a texture, GLuint returned is the texture ID*/
    GLuint loadTexture(const char* fileName) {
		return SOIL_load_OGL_texture(fileName,
                                   SOIL_LOAD_AUTO,
                                   SOIL_CREATE_NEW_ID,
                                   SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    }



  }texture;

}
