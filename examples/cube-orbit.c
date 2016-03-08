#include "util.h"

#define WINDOW_NAME "CubeExample"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

// model
typedef struct Cube Cube;
struct Cube {
  glisy_geometry geometry;
  glisy_uniform uModel;

  vec3 position;
  vec3 scale;

  mat4 translation;
  mat4 transform;
  mat4 rotation;

  int faceslen;
};

// forward decl
static void InitializeCube(Cube *cube);
static void UpdateCube(Cube *cube);
static void RotateCube(Cube *cube, float radians);

// objects
#define numberOfCubes 100
static int cubeID = 0;
static Cube cubes[numberOfCubes];

// cube constructor
void
InitializeCube(Cube *cube) {
  const int id = cubeID++;
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

  int hex = 0xFF7F50FF + (id * 0xffffff);
  glisy_color color;
  glisy_color_init(&color, 0, hex);

  const vec3 colors[] = {
    vec3(color.r, color.g, color.b),
    vec3(color.r, color.g, color.b),
    vec3(color.r, color.g, color.b),
    vec3(color.r, color.g, color.b),
    vec3(color.r, color.g, color.b),
    vec3(color.r, color.g, color.b),
    vec3(color.r, color.g, color.b),
    vec3(color.r, color.g, color.b),
  };

  const GLushort faces[] = {
    0, 1, 3, 0, 3, 2,
    1, 5, 7, 1, 7, 3,
    5, 4, 6, 5, 6, 7,
    4, 0, 2, 4, 2, 6,
    4, 5, 1, 4, 1, 0,
    2, 3, 7, 2, 7, 6,
  };

  cube->position = vec3(1, 1, 1);
  cube->scale = vec3(1, 1, 1);
  cube->faceslen  = sizeof(faces) / sizeof(GLushort);
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

  glisy_vao_attribute vColor = {
    .buffer = {
      .data = (void *) colors,
      .type = GL_FLOAT,
      .size = size,
      .usage = GL_STATIC_DRAW,
      .offset = 0,
      .stride = 0,
      .dimension = 3,
    }
  };

  mat4_identity(cube->translation);
  mat4_identity(cube->transform);
  mat4_identity(cube->rotation);

  // init uniforms
  glisy_uniform_init(&cube->uModel, "uModel", GLISY_UNIFORM_MATRIX, 4);

  // vao attributes
  glisy_geometry_init(&cube->geometry);
  glisy_geometry_attr(&cube->geometry, "vColor", &vColor);
  glisy_geometry_attr(&cube->geometry, "vPosition", &vPosition);

  glisy_geometry_faces(&cube->geometry,
                       GL_UNSIGNED_SHORT,
                       cube->faceslen,
                       (void *) faces);

  glisy_geometry_update(&cube->geometry);

  UpdateCube(cube);
}

void
UpdateCube(Cube *cube) {
  mat4 model;
  mat4_identity(model);
  model = mat4_scale(model, cube->scale);
  model = mat4_multiply(model, cube->rotation);
  model = mat4_multiply(model, cube->translation);
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
RotateCartesianCube(Cube *cube, double x, double y) {
  const float angle = 20.0f;
  const float radians = dtor(angle);
  vec3 current = cube->position;
  vec3 target = vec3(x, y, current.z);
  vec3 interpolated = vec3_lerp(current, target, 0.7);

  mat4_rotate(cube->rotation, radians, interpolated);
  UpdateCube(cube);
}

void
RotateCube(Cube *cube, float radians) {
  (void) mat4_rotate(cube->rotation, radians, cube->position);
}

void
TranslateCube(Cube *cube, vec3 translation) {
  cube->position = vec3_add(cube->position, translation);
  cube->translation  = mat4_translate(cube->translation, translation);
  UpdateCube(cube);
}

void
ScaleCube(Cube *cube, vec3 scale) {
  cube->scale = scale;
  UpdateCube(cube);
}

static void
onMouseMove(GLFWwindow* window, double x, double y) {
  Camera *camera = (Camera *) glfwGetWindowUserPointer(window);
  camera->target.x = x;
  camera->target.y = y;
  UpdateCamera(camera);
}

static void
onMouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
  Camera *camera = (Camera *) glfwGetWindowUserPointer(window);
  camera->fov += yoffset;
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

  // params
  const float radius = 100.0f;

  // init gl
  GL_CONTEXT_INIT();
  glfwSetScrollCallback(window, onMouseScroll);
  glfwSetCursorPosCallback(window, onMouseMove);
  glfwSetWindowUserPointer(window, &camera);

  program = CreateProgram("cube-orbit.v.glsl", "cube-orbit.f.glsl");

  InitializeCamera(&camera, WINDOW_WIDTH, WINDOW_HEIGHT);

  for (int i = 0, j = numberOfCubes; i < numberOfCubes; ++i, ++j) {
    Cube *cube = &cubes[i];
    vec3 scale = {j + 1, j + 1, j + 1};
    vec3 translation = vec3(0, 0, 0);

    if (i > 0) {
      translation.y = sinf(i) * radius;
      translation.z = cosf(i) * radius;
    }

    InitializeCube(cube);
    ScaleCube(cube, scale);
    TranslateCube(cube, translation);
  }

  {
    double x = 0;
    double y = 0;
    glfwGetCursorPos(window, &x, &y);
    camera.target.x = x;
    camera.target.y = y;
    UpdateCamera(&camera);
  }

  GL_RENDER({
    const float time = glfwGetTime();
    const float angle = time * 22.5f;
    const float radians = dtor(angle);
    const float camX = sinf(radians) * radius;
    const float camY = -cosf(radians) * radius;
    const float camZ = cosf(radians) * radius;
    const vec3 rotation = vec3(1, 0, 0);
    (void) mat4_rotate(camera.transform,
                       radians,
                       rotation);

    camera.aspect = width / height;
    UpdateCamera(&camera);

    for (int i = 0; i < numberOfCubes; ++i) {
      RotateCube(&cubes[i], radians * 4);
      RotateCartesianCube(&cubes[i], camX, camY);
      DrawCube(&cubes[i]);
    }

  });

  return 0;
}
