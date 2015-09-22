#ifndef GLISY_WINDOW_H
#define GLISY_WINDOW_H

#include <glisy/gl.h>

/**
 * Default window dimension.
 */

#define GLISY_DEFAULT_WINDOW_WIDTH 640
#define GLISY_DEFAULT_WINDOW_HEIGHT 480

/**
 * glisy window.
 */

typedef struct glisy_window glisy_window;
struct glisy_window {

  /**
   * glisy window height.
   */

  int height;

  /**
   * glisy window width.
   */

  int width;

  /**
   * Underlying glfw window pointer.
   */

  GLFWwindow *viewport;
};

/**
 * Sets glisy window width.
 */

void
glisy_window_set_width (glisy_window *, int);

/**
 * Sets glisy window height.
 */

void
glisy_window_set_height (glisy_window *, int);

/**
 * Set glisy window size.
 */

void
glisy_window_set_size (glisy_window *, int, int);

/**
 * Updates window state.
 */

void
glisy_window_update (const glisy_window);

#endif
