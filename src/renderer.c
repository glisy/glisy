#include <glisy/window.h>
#include <glisy/renderer.h>

void
glisy_renderer_size (glisy_renderer this, int width, int height) {
  glisy_window *window = &this.ctx.window;
  glisy_window_set_size(window, width, height);
}

void
glisy_renderer_update (glisy_renderer this) {
  // update window
  glisy_window_update(this.ctx.window);
}
