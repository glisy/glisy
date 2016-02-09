#ifndef GLISY_RENDERER_H
#define GLISY_RENDERER_H

#include <glisy/gl.h>

/**
 * Glisy Renderer structure type.
 */

typedef struct glisy_renderer glisy_renderer;
struct glisy_renderer {

  // renderer width
  GLint width;

  // renderer width
  GLint height;

};

/**
 * Set Glisy Renderer viewport width and height.
 * @param renderer - Glisy Renderer struct
 * @param width    - Glisy Renderer viewport width
 * @param height   - Glisy Renderer viewport height
 */

void
glisy_renderer_size(const glisy_renderer renderer, GLint width, GLint height);

/**
 * Update Glisy Renderer state.
 * @param renderer - Glisy Renderer struct
 */

void
glisy_renderer_update(const glisy_renderer renderer);

#endif
