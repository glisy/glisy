#include "util.h"

#define WINDOW_NAME "GridExample"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

#define DEPTH 32
#define NUM_VERTICES (DEPTH+1)*(DEPTH+1)
#define NUM_INDICES 2*3*DEPTH*DEPTH

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
    GLuint faces[2 * 100 * 101 * 2];
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
  vec3 vertices[101][101];
  GLuint faces[2 * 100 * 101 * 2];

  for (int i = 0; i < 101; i++) {
    for (int j = 0; j < 101; j++) {
      vertices[i][j].x = (j - 50) / 50.0;
      vertices[i][j].y = (i - 50) / 50.0;
    }
  }

  grid->position = vec3(0, 0, 0);
  grid->scale = vec3(1, 1, 1);
  grid->vertex.length = DEPTH;
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

  printf("%d\n", size);
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
                       GL_UNSIGNED_INT,
                       grid->vertex.length,
                       grid->vertex.faces);
  UpdateGrid(grid);
}

void
UpdateGrid(Grid *grid) {
  mat4 model;
  mat4_identity(model);
  model = mat4_scale(model, grid->scale);
  model = mat4_multiply(model, grid->rotation);
  model = mat4_multiply(model, grid->translation);
  glisy_uniform_set(&grid->uModel, &model, sizeof(model));
  glisy_uniform_bind(&grid->uModel, &program);
}

void
DrawGrid(Grid *grid) {
  UpdateGrid(grid);
  glisy_geometry_bind(&grid->geometry, &program);
  for (int i = 0; i < 101; i++) {
    glisy_geometry_draw(&grid->geometry, GL_LINE_STRIP, 101 * i, grid->vertex.length);
  }
  glisy_geometry_unbind(&grid->geometry);
}

static void
onMouseMove(GLFWwindow* window, double x, double y) {
  const float angle = 45.0f;
  const float radians = dtor(angle);
  const float radius = 10.0f;
  const float camX = sinf(radians) * radius;
  const float camY = -cosf(radians) * radius;
  const float camZ = cosf(radians) * radius;

  camera.target.x = x;
  camera.target.y = y;
  camera.target.z = camZ;
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
  program = CreateProgram("grid.v.glsl", "grid.f.glsl");

  InitializeCamera(&camera, WINDOW_WIDTH, WINDOW_HEIGHT);
  InitializeGrid(&grid);

  GL_RENDER({
    const float time = glfwGetTime();
    const float angle = time * 45.0f;
    const float radians = dtor(angle);
    const float radius = 10.0f;
    const float camX = sinf(radians) * radius;
    const float camY = -cosf(radians) * radius;
    const float camZ = cosf(radians) * radius;

    //camera.target.x = camX;
    //camera.target.y = camY;
    camera.target.z = camZ;

    camera.aspect = width / height;
    UpdateCamera(&camera);
  });

  return 0;
}
