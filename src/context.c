
#include <stdio.h>
#include <glisy/gl.h>
#include <glisy/events.h>
#include <glisy/window.h>
#include <glisy/context.h>

void
glisy_context_init (glisy_context *this) {
  const char *name = this->name;
  glisy_window *window = &this->window;
  glisy_events *events = &this->events;

  if (!window->width) {
    window->width = GLISY_DEFAULT_WINDOW_WIDTH;
  }

  if (!window->height) {
    window->height = GLISY_DEFAULT_WINDOW_HEIGHT;
  }

  window->viewport = glfwCreateWindow(window->width,
                                      window->height,
                                      name,
                                      NULL, // @TODO(werle) - monitor
                                      NULL); // @TODO(werle) - shared window

  if (NULL == window->viewport) {
    // @TODO(werle) - Handle error
    return;
  }

  // make this window viewport the current context window
  glfwMakeContextCurrent(window->viewport);

  // set buffer swap interval
  // @TODO(werle) - Make this configurable
  glfwSwapInterval(1);

  // set event handlers
  if (events->on.key) {
    glfwSetKeyCallback(window->viewport, events->on.key);
  }
}

int
glisy_context_should_update (const glisy_context this) {
  int update = 1;
  if (glfwWindowShouldClose(this.window.viewport)) update = 0;
  return update;
}

void
glisy_context_use (glisy_context *this, const void *data) {
  this->data = (void *) data;
}
