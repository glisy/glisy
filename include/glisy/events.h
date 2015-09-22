#ifndef GLISY_EVENTS_H
#define GLISY_EVENTS_H
#include <glisy/gl.h>

/**
 * Event delegation handler.
 */

typedef struct glisy_events glisy_events;
struct glisy_events {

  /**
   * Event callbacks.
   */

  struct {

    /**
     * GLFW key press handler.
     */

    void (*key) (GLFWwindow *window,
                 int key,
                 int scancode,
                 int action,
                 int mods);

    /**
     * GLFW error handler.
     */

    void (*error) (int error,
                   const char *message);
  } on;
};
#endif
