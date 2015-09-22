
#include <glisy/glisy.h>

int
glisy_init () {
  if (GL_TRUE != glfwInit()) {
    // @TODO(werle) - handle error
    return 0;
  }
  return 1;
}

void
glisy_terminate (void) {
  glfwTerminate();
}
