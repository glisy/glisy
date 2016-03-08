#include "util.h"

#define WINDOW_NAME "GridExample"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

// model
typedef struct Grid Grid;
struct Grid {
  glisy_geometry geometry;
  glisy_uniform uModel;

  vec3 position;
  vec3 scale;

  mat4 translation;
  mat4 transform;
  mat4 rotation;

  struct {
    vec3 positions[101][101];
    GLushort faces[2 * 100 * 101 * 2];
    GLuint length;
  } vertex;

  struct {
    glisy_vao_attribute vPosition;
    glisy_vao_attribute vColor;
  } attributes;
};

// forward decl
static void InitializeGrid(Grid *grid);
static void UpdateGrid(Grid *grid);
static void RotateGrid(Grid *grid, float radians);

// glfw
static GLFWwindow *window;

// glisy
static glisy_program program;

// objects
static Camera camera;
static Grid grid;

// grid constructor
void
InitializeGrid(Grid *grid) {
  int vertexLength = 101;
  int facesLen = 0;
  vec3 vertices[101][101];
  GLushort faces[2 * 100 * 101 * 2];

  for (int i = 0; i < 101; i++) {
    for (int j = 0; j < 101; j++) {
      vertices[i][j].x = (j - 50) / 100.0;
      vertices[i][j].z = (i - 50) / 100.0;
      vertices[i][j].y = 0;
    }
  }

  {
    int i = 0;

    // Horizontal grid lines
    for (int y = 0; y < 101; y++) {
      for (int x = 0; x < 100; x++) {
        faces[i++] = y * 101 + x;
        faces[i++] = y * 101 + x + 1;
      }
    }

    // Vertical grid lines
    for (int x = 0; x < 101; x++) {
      for (int y = 0; y < 100; y++) {
        faces[i++] = y * 101 + x;
        faces[i++] = (y + 1) * 101 + x;
      }
    }

    facesLen = i;
  }

  grid->position = vec3(0, 0, 1);
  grid->scale = vec3(1, 1, 1);
  grid->vertex.length = 2 * 100 * 101 * 2;
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

  memcpy(grid->vertex.positions, vertices, size);
  memcpy(grid->vertex.faces, faces, sizeof(faces));

  grid->attributes.vPosition = vPosition;

  mat4_identity(grid->translation);
  mat4_identity(grid->transform);
  mat4_identity(grid->rotation);

  glisy_uniform_init(&grid->uModel,
                     "uModel",
                     GLISY_UNIFORM_MATRIX, 4);

  glisy_geometry_init(&grid->geometry);
  glisy_geometry_attr(&grid->geometry,
                      "vPosition",
                      &grid->attributes.vPosition);

  glisy_geometry_faces(&grid->geometry,
                       GL_UNSIGNED_SHORT,
                       facesLen,
                       faces);

  glisy_geometry_update(&grid->geometry);
  UpdateGrid(grid);
}

void
UpdateGrid(Grid *grid) {
  mat4 model;
  mat4 scale;
  mat4 rotation;
  mat4 translation;

  mat4_identity(model);
  mat4_identity(scale);
  mat4_identity(rotation);
  mat4_identity(translation);

  mat4_scale(scale, grid->scale);

  mat4_copy(translation, grid->translation);
  mat4_translate(translation, grid->position);

  mat4_copy(rotation, grid->rotation);

  model = mat4_multiply(model, scale);
  model = mat4_multiply(model, rotation);
  model = mat4_multiply(model, translation);

  glisy_uniform_set(&grid->uModel, &model, sizeof(model));
  glisy_uniform_bind(&grid->uModel, &program);
}

void
DrawGrid(Grid *grid) {
  UpdateGrid(grid);
  glisy_geometry_bind(&grid->geometry, &program);
  glisy_geometry_draw(&grid->geometry, GL_LINES, 0, grid->vertex.length);
  glisy_geometry_unbind(&grid->geometry);
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

  program = CreateProgram("grid.v.glsl", "grid.f.glsl");

  InitializeCamera(&camera, WINDOW_WIDTH, WINDOW_HEIGHT);
  InitializeGrid(&grid);

  (void) mat4_rotate(camera.transform, dtor(90), vec3(0, 1, 0));
  grid.position.y = 1;

  GL_RENDER({
    const float time = glfwGetTime();
    const float angle = time * 45.0f;
    const float radians = dtor(angle);
    const vec3 rotation = vec3(0, 1, 0);

    (void) mat4_rotate(camera.transform,
                       radians,
                       rotation);

    camera.aspect = width / height;
    UpdateCamera(&camera);
    DrawGrid(&grid);
  });

  return 0;
}
