/*SOIL should only ever touch this file since its directly related to textures*/
#pragma once

#include "../opengl.hpp"

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

	void init() {
		width = 0;
		height = 0;
		textureFormat = GL_RGB8;
		imageFormat = GL_RGB8;
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

		//Set the wrapping and (possible) filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);

		//unbind bc we no longer need it
		glBindTexture(GL_TEXTURE_2D, 0);
    }


    void bind() const {
		  glBindTexture(GL_TEXTURE_2D, textureID);
    }


  };

}
