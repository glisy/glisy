#include "util.h"
#include "bunny.h"

#define WINDOW_NAME "StanfordBunny"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

#define MAX_FOV 179
#define MIN_FOV 1

// model
typedef struct Bunny Bunny;
struct Bunny {
  glisy_geometry geometry;
  int faceslen;
};

// forward decl
static void InitializeBunny(Bunny *bunny);

// bunny constructor
void
InitializeBunny(Bunny *bunny) {
  glisy_vao_attribute vPosition = {
    .buffer = {
      .data = (void *) StanfordBunny.positions,
      .type = GL_FLOAT,
      .size = sizeof(StanfordBunny.positions),
      .usage = GL_STATIC_DRAW,
      .offset = 0,
      .stride = 0,
      .dimension = 3,
    }
  };

  bunny->faceslen = 3 * STANFORD_BUNNY_CELLS_COUNT;

  glisy_geometry_init(&bunny->geometry);
  glisy_geometry_attr(&bunny->geometry, "vPosition", &vPosition);
  glisy_geometry_faces(&bunny->geometry,
                       GL_UNSIGNED_SHORT,
                       bunny->faceslen,
                       (void *) StanfordBunny.cells);

  glisy_geometry_update(&bunny->geometry);
}

void
DrawBunny(Bunny *bunny) {
  glisy_geometry_bind(&bunny->geometry, 0);
  glisy_geometry_draw(&bunny->geometry, GL_TRIANGLES, 0, bunny->faceslen);
  glisy_geometry_unbind(&bunny->geometry);
}

static void
onMouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
  Camera *camera = (Camera *) glfwGetWindowUserPointer(window);
  camera->fov += yoffset;
  camera->fov = min(MAX_FOV, max(camera->fov, MIN_FOV));
  UpdateCamera(camera);
}

int
main(void) {
  // glfw
  GLFWwindow *window;

  // glisy
  glisy_program program;

  // objects
  Camera camera;
  Bunny bunny;

  GL_CONTEXT_INIT();
  glfwSetScrollCallback(window, onMouseScroll);

  program = CreateProgram("bunny.v.glsl", "bunny.f.glsl");

  InitializeCamera(&camera, WINDOW_WIDTH, WINDOW_HEIGHT);
  InitializeBunny(&bunny);
  glfwSetWindowUserPointer(window, &camera);

  camera.position = vec3(1, 4, 10);
  camera.target = vec3(1, 1, 1);

  glisy_program_bind(&program);
  GL_RENDER({
    const float time = glfwGetTime();
    const float angle = time * 22.5f;
    const float radians = dtor(angle);
    const vec3 rotation = vec3(1, 1, 1);
    (void) mat4_rotate(camera.transform,
                       radians,
                       rotation);

    camera.aspect = width / height;
    UpdateCamera(&camera);
    DrawBunny(&bunny);
  });

  return 0;
}
