#include <stdio.h>
#include <glisy/gl.h>
#include <glisy/context.h>

void
glisy_context_init (glisy_context *this) {
}

int
glisy_context_should_update (glisy_context *this) {
  int update = 1;
  return update;
}

void
glisy_context_use (glisy_context *this, const void *data) {
  this->data = (void *) data;
}
