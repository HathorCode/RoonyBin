/*SOIL should only ever touch this file since its directly related to textures*/
#pragma once

#include "engine/opengl.hpp"

namespace rb {
  struct Texture {
    GLuint textureID;
    GLuint width, height; // of the texture

    GLuint textureFormat;
    GLuint imageFormat;

    GLuint wrapS;
    GLuint wrapT;

    // In case we might need to scale, which seems unnecessary
    GLuint filterMax;
    GLuint filterMin;

    Texture() {
		width = 0;
		height = 0;
		textureFormat = GL_RGB;
		imageFormat = GL_RGB;
		wrapS = GL_REPEAT;
		wrapT = GL_REPEAT;
		filterMax = (GL_LINEAR);
		filterMin = (GL_LINEAR);

      glGenTextures(1, &textureID);
    }

    /*char array data is the taken data from loading in the image.
    Meaning we should use load image, not load texture from soil */
	void generate(GLuint widthParam, GLuint heightParam, unsigned char* data) {
		width = widthParam;
		height = heightParam;

		// Now I create the texture
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);

		//Set the wrapping and (possible) filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);

		//unbind bc we no longer need it
		glBindTexture(GL_TEXTURE_2D, 0);
    }


    void bind() {
		  glBindTexture(GL_TEXTURE_2D, textureID);
    }


  };

}
