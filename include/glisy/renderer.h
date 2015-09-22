#ifndef GLISY_RENDERER_H
#define GLISY_RENDERER_H

#include <glisy/context.h>

/**
 * glisy renderer structure.
 */

typedef struct glisy_renderer glisy_renderer;
struct glisy_renderer {

  /**
   * Our known rendering context.
   */

  glisy_context ctx;
};

/**
 * Set renderer viewport size with
 * width and height.
 */

void
glisy_renderer_size (const glisy_renderer, int, int);

/**
 * Updates render state.
 */

void
glisy_renderer_update (const glisy_renderer);
#endif
