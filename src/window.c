#include <glisy/window.h>

void
glisy_window_set_width (glisy_window *this, int width) {
  this->width = width;
}

void
glisy_window_set_height (glisy_window *this, int height) {
  this->height = height;
}

void
glisy_window_set_size (glisy_window *this, int width, int height) {
  this->width = width;
  this->height = height;
}

void
glisy_window_update (const glisy_window this) {

}
