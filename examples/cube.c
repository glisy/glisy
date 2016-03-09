#include "util.h"

#define WINDOW_NAME "CubeExample"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

// model
typedef struct Cube Cube;
struct Cube {
  // glisy
  glisy_geometry geometry;
  glisy_uniform uModel;

  // gl
  vec3 position;
  mat4 transform;
  mat4 rotation;

  // vao
  int faceslen;
};

// forward decl
static void InitializeCube(Cube *cube);
static void UpdateCube(Cube *cube);
static void RotateCube(Cube *cube, float radians, vec3 axis);

// cube constructor
void
InitializeCube(Cube *cube) {
  const vec3 vertices[] = {
    vec3(-0.5, -0.5, +0.5),
    vec3(+0.5, -0.5, +0.5),
    vec3(-0.5, +0.5, +0.5),
    vec3(+0.5, +0.5, +0.5),

    vec3(-0.5, -0.5, -0.5),
    vec3(+0.5, -0.5, -0.5),
    vec3(-0.5, +0.5, -0.5),
    vec3(+0.5, +0.5, -0.5),
  };

  // init color
  glisy_color color;
  glisy_color_init(&color, "blue", 0);

  // init uniforms
  glisy_uniform uColor;
  glisy_uniform_init(&uColor, "uColor", GLISY_UNIFORM_VECTOR, 3);
  glisy_uniform_init(&cube->uModel, "uModel", GLISY_UNIFORM_MATRIX, 4);

  // set uniforms
  glisy_uniform_set(&uColor, &vec3(color.r, color.g, color.b), sizeof(vec3));
  glisy_uniform_bind(&uColor, 0);

  const GLushort faces[] = {
    0, 1, 3, 0, 3, 2,
    1, 5, 7, 1, 7, 3,
    5, 4, 6, 5, 6, 7,
    4, 0, 2, 4, 2, 6,
    4, 5, 1, 4, 1, 0,
    2, 3, 7, 2, 7, 6,
  };

  cube->position = vec3(0, 0, 0);
  cube->faceslen = sizeof(faces) / sizeof(GLushort);
  GLuint size = sizeof(vertices);

  glisy_vao_attribute vPosition = {
    .buffer = {
      .data = (void *) vertices,
      .type = GL_FLOAT,
      .size = size,
      .usage = GL_STATIC_DRAW,
      .offset = 0,
      .stride = 0,
      .dimension = 3,
    }
  };

  // init matrices
  mat4_identity(cube->transform);
  mat4_identity(cube->rotation);

  // init vao attributes
  glisy_geometry_init(&cube->geometry);
  glisy_geometry_attr(&cube->geometry, "vPosition", &vPosition);

  glisy_geometry_faces(&cube->geometry,
                       GL_UNSIGNED_SHORT,
                       cube->faceslen,
                       (void *) faces);

  // update geometry with attributes and faces
  glisy_geometry_update(&cube->geometry);

  UpdateCube(cube);
}

void
UpdateCube(Cube *cube) {
  mat4 model;
  mat4_identity(model);
  model = mat4_multiply(model, cube->rotation);
  glisy_uniform_set(&cube->uModel, &model, sizeof(model));
  glisy_uniform_bind(&cube->uModel, 0);
}

void
DrawCube(Cube *cube) {
  UpdateCube(cube);
  glisy_geometry_bind(&cube->geometry, 0);
  glisy_geometry_draw(&cube->geometry, GL_TRIANGLES, 0, cube->faceslen);
  glisy_geometry_unbind(&cube->geometry);
}

void
RotateCube(Cube *cube, float radians, vec3 axis) {
  (void) mat4_rotate(cube->rotation, radians, axis);
}

int
main(void) {
  // glfw
  GLFWwindow *window;

  // glisy
  glisy_program program;

  // objects
  Camera camera;
  Cube cube;

  // init
  GL_CONTEXT_INIT();
  program = CreateProgram("cube.v.glsl", "cube.f.glsl");
  InitializeCamera(&camera, WINDOW_WIDTH, WINDOW_HEIGHT);
  InitializeCube(&cube);

  // move camera behind cube
  camera.position = vec3(1, 1, 1);

  GL_RENDER({
    const float time = glfwGetTime();
    const float angle = time * 45.0f;
    const float radians = dtor(angle);
    const vec3 rotation = vec3(0, 1, 0);
    (void) mat4_rotate(camera.transform,
                       radians,
                       rotation);

    // handle resize
    camera.aspect = width / height;

    // update camera orientation
    UpdateCamera(&camera);

    // rotate cube at radians angle in opposite direction
    RotateCube(&cube, radians, vec3_negate(rotation));

    // render cube
    DrawCube(&cube);
  });

  return 0;
}
