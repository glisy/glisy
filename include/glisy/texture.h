#ifndef GLISY_TEXTURE_H
#define GLISY_TEXTURE_H

#include <glisy/gl.h>

/**
 * Glisy Texture Options structure type.
 */

typedef struct glisy_texture_options glisy_texture_options;
struct glisy_texture_options {

  // Glisy Texture format.
  GLuint format;

  // Glisy Texture width.
  GLuint width;

  // Glisy Texture height.
  GLuint height;

};

/**
 * Glisy Texture structure type.
 */

typedef struct glisy_texture glisy_texture;
struct glisy_texture {

  // Glisy Texture ID.
  GLuint id;

};

/**
 * Glisy Texture initializer.
 * @param options - Glisy Texture Options struct
 */

GLboolean
glisy_texture_init(glisy_texture_options options);

#endif
