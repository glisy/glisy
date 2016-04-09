#ifndef GLISY_TEXTURE_H
#define GLISY_TEXTURE_H

#include <glisy/gl.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Texture mapping types.
 */

enum {
  GLISY_UV_MAPPING = 1,
};

/**
 * GlisyTexture struct type.
 */

typedef struct GlisyTexture GlisyTexture;
struct GlisyTexture {
  GLchar *name;

  GLuint handle;
  GLuint mapping;
  GLuint shape[4];
  GLuint channels;
  GLuint anisotropy;
  GLuint unpackAlignment;

  GLenum type;
  GLenum wrapS;
  GLenum wrapT;
  GLenum target;
  GLenum format;
  GLenum minFilter;
  GLenum magFilter;

  GLboolean compressed;
};

/**
 * Initializes a GlisyTexture with target where target is one of:
 * - GL_TEXTURE_1D
 * - GL_TEXTURE_2D
 * - GL_TEXTURE_3D
 */

void
glisyTextureInit(GlisyTexture *texture, GLenum taret);

/**
 * Binds a GlisyTexture with glBindTexture using the handle
 * created with glGenTextures and the texture set with
 * glisyTextureInit.
 */

void
glisyTextureBind(GlisyTexture *texture);

/**
 * Binds texture at slot index.
 */


void
glisyTextureBindSlot(GlisyTexture *texture, GLuint slot);

/**
 * Unbinds texture.
 */

void
glisyTextureUnbind(GlisyTexture *texture);

/**
 * Disposes of a GlisyTexture and the internal handle
 * created by glGenTextures. This will reset the handle
 * value and texture.
 */

void
glisyTextureDispose(GlisyTexture *texture);

/**
 * Sets texture to active texture at slot.
 */

void
glisyTextureActive(GlisyTexture *texture, GLuint slot);

/**
 * Generates mipmaps based on the current shape and calls
 * glGenerateMipmap on the internal texture texture.
 */

void
glisyTextureGenerateMipmap(GlisyTexture *texture);

/**
 * Updates a GlisyTexture with pixel data, shape (width, height),
 * size, offset, and level.
 */

void
glisyTextureUpdate(GlisyTexture *texture,
                   GLvoid **pixels,
                   GLuint *shape,
                   GLsizei size,
                   GLuint *offset,
                   GLuint level);

#ifdef __cplusplus
}
#endif
#endif
