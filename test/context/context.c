#include <stdio.h>
#include <assert.h>
#include <glisy/glisy.h>

typedef struct data_t data_t;
struct data_t { int id; };

int
main (void) {
  glisy_init();
  glisy_context ctx;
  int id = rand();
  data_t data = {id};

  ctx.name = "Glisy Context Text";

  // init context
  glisy_context_use(&ctx, &data);
  glisy_context_init(&ctx);

  // ensure defaults were used
  assert(ctx.window.height == GLISY_DEFAULT_WINDOW_HEIGHT);
  assert(ctx.window.width == GLISY_DEFAULT_WINDOW_WIDTH);
  assert(0 == strcmp(ctx.name, ctx.window.name));

  assert(id == ((data_t *) ctx.data)->id);
  assert(glisy_context_should_update(&ctx));
  return 0;
}
