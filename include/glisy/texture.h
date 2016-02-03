#ifndef GLISY_TEXTURE_H
#define GLISY_TEXTURE_H
#include <glisy/gl.h>

typedef struct glisy_texture_options glisy_texture_options;
struct glisy_texture_options {
  GLuint format;
  unsigned int width;
  unsigned int height;
};

typedef struct glisy_texture glisy_texture;
struct glisy_texture {
  GLuint id;
};


glisy_texture_init (glisy_texture_options);
#endif
