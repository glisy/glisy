#include <stdio.h>
#include <stdlib.h>

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

  struct {
    vec3 positions[8];
    vec3 colors[8];
    GLushort faces[36];
    GLuint length;
  } vertex;

  struct {
    glisy_vao_attribute vPosition;
    glisy_vao_attribute vColor;
  } attributes;
};

// forward decl
static void InitializeCube(Cube *cube);
static void UpdateCube(Cube *cube);
static void RotateCube(Cube *cube, float radians);

// glfw
static GLFWwindow *window;

// glisy
static glisy_program program;

// objects
#define numberOfCubes 10
static int cubeID = 0;
static Camera camera;
static Cube cubes[numberOfCubes];

// colors
static glisy_color cubeColors[numberOfCubes] = {
  {"blue"},
  {"cyan"},
  {"green"},
  {"purple"},
  {"yellow"},
  {"salmon"},
  {"silver"},
  {"palegreen"},
  {"mintcream"},
  {"papayawhip"},
};

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

  const vec3 colors[] = {
    vec3(cubeColors[id].r, cubeColors[id].g, cubeColors[id].a),
    vec3(cubeColors[id].r, cubeColors[id].g, cubeColors[id].a),
    vec3(cubeColors[id].r, cubeColors[id].g, cubeColors[id].a),
    vec3(cubeColors[id].r, cubeColors[id].g, cubeColors[id].a),

    vec3(cubeColors[id].r, cubeColors[id].g, cubeColors[id].a),
    vec3(cubeColors[id].r, cubeColors[id].g, cubeColors[id].a),
    vec3(cubeColors[id].r, cubeColors[id].g, cubeColors[id].a),
    vec3(cubeColors[id].r, cubeColors[id].g, cubeColors[id].a),
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
  cube->vertex.length = sizeof(faces) / sizeof(GLushort);
  GLuint size = sizeof(vertices);

  glisy_vao_attribute vPosition = {
    .buffer = {
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
      .type = GL_FLOAT,
      .size = size,
      .usage = GL_STATIC_DRAW,
      .offset = 0,
      .stride = 0,
      .dimension = 3,
    }
  };

  cube->attributes.vPosition = vPosition;
  cube->attributes.vColor = vColor;

  memcpy(cube->vertex.positions, vertices, size);
  memcpy(cube->vertex.colors, colors, size);
  memcpy(cube->vertex.faces, faces, sizeof(faces));

  cube->attributes.vPosition.buffer.data = (void *) vertices;
  cube->attributes.vColor.buffer.data = (void *) colors;

  mat4_identity(cube->translation);
  mat4_identity(cube->transform);
  mat4_identity(cube->rotation);

  glisy_uniform_init(&cube->uModel, "uModel", GLISY_UNIFORM_MATRIX, 4);

  glisy_geometry_init(&cube->geometry);

  glisy_geometry_attr(&cube->geometry,
                      "vColor",
                      &cube->attributes.vColor);

  glisy_geometry_attr(&cube->geometry,
                      "vPosition",
                      &cube->attributes.vPosition);

  glisy_geometry_faces(&cube->geometry,
                       GL_UNSIGNED_SHORT,
                       cube->vertex.length,
                       cube->vertex.faces);

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
  glisy_uniform_bind(&cube->uModel, &program);
}

void
DrawCube(Cube *cube) {
  UpdateCube(cube);
  glisy_geometry_bind(&cube->geometry, &program);
  glisy_geometry_draw(&cube->geometry, GL_TRIANGLES, 0, cube->vertex.length);
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
  camera.target.x = x;
  camera.target.y = -y;
  UpdateCamera(&camera);
}

static void
onMouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
  camera.fov += yoffset;
  UpdateCamera(&camera);
}

int
main(void) {
  GL_CONTEXT_INIT();
  glfwSetScrollCallback(window, onMouseScroll);
  glfwSetCursorPosCallback(window, onMouseMove);

  program = CreateProgram("cube.v.glsl", "cube.f.glsl");

  InitializeCamera(&camera, WINDOW_WIDTH, WINDOW_HEIGHT);

  // init colors and cubes
  for (int i = 0; i < numberOfCubes; ++i) {
    glisy_color *color = &cubeColors[i];
    glisy_color_init(color, strdup(color->name), 0);
  }

  for (int i = 0; i < numberOfCubes; ++i) {
    Cube *cube = &cubes[i];
    vec3 scale = {i + 1, i + 1, i + 1};
    vec3 translation = {1 - i, i, i + 1};
    if (i > 0) {
      translation.y = -sinf(i) * 50;
    }

    if (i % 2) {
      translation = vec3_negate(translation);
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
    camera.target.y = -y;
    UpdateCamera(&camera);
  }

  GL_RENDER({
    const float time = glfwGetTime();
    const float angle = time * 45.0f;
    const float radians = dtor(angle);
    const float radius = 10.0f;
    const float camX = sinf(radians) * radius;
    const float camY = -cosf(radians) * radius;
    const float camZ = cosf(radians) * radius;

    camera.target.z = camZ;

    camera.aspect = width / height;
    UpdateCamera(&camera);

    for (int i = 0; i < numberOfCubes; ++i) {
      RotateCube(&cubes[i], radians);
      RotateCartesianCube(&cubes[i], camX, camY);
      DrawCube(&cubes[i]);
    }

  });

  return 0;
}
