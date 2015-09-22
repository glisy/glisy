#include <stdio.h>
#include <assert.h>
#include <glisy/glisy.h>

typedef struct user_data user_data;
struct user_data {
  int id;
};

static void
onerror (int error, const char *message) {
  fputs(message, stderr);
}

static void
onkeypress (GLFWwindow* window, int key, int scancode, int action, int mods) {
  printf("key press %d %d\n", key, action);
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}


int
main (void) {
  glisy_init();
  glisy_context ctx;
  user_data data;
  int id = rand();
  data.id = id;

  // meta
  ctx.name = "Glisy Context Text";

  // set event handlers
  ctx.events.on.key = onkeypress;
  ctx.events.on.error = onerror;

  // setup window
  //ctx.window.width = 600;
  //ctx.window.height = 600;

  // init context
  glisy_context_use(&ctx, &data);
  glisy_context_init(&ctx);

  // ensure viewport creation
  assert(ctx.window.viewport);

  // ensure defaults were used
  assert(ctx.window.height == GLISY_DEFAULT_WINDOW_HEIGHT);
  assert(ctx.window.width == GLISY_DEFAULT_WINDOW_WIDTH);

  // ensure user data is set
  assert(id == ((user_data *) ctx.data)->id);

  // we should be able to update
  assert(glisy_context_should_update(ctx));
  return 0;
}
