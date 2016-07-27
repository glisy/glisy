#include <glisy/geometry.h>
#include <glisy/camera.h>
#include <glisy/math.h>
#include "util.h"

#define WINDOW_NAME "GridExample"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

#define MAX_FOV 179
#define MIN_FOV 1

#define GRID_DEPTH 100
#define GRID_WIDTH 100
#define GRID_HEIGHT 100
#define GRID_FACES_LENGTH 2 * (GRID_WIDTH - 1) * 2 * GRID_HEIGHT

// model
typedef struct Grid Grid;
struct Grid {
  GlisyGeometry geometry;
  GlisyUniform model;
  vec3 position;
  vec3 scale;
};

static mat4 transform;
static float aspect = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
static float near = 1.0;
static float far = 1000.0;
static float fov = M_PI / 2.0;

static GlisyProgram program;
static GlisyCamera camera;
static GLFWwindow *window;
static Grid grid;

// forward decl
static void InitializeGrid(Grid *grid);
static void UpdateGrid(Grid *grid);

// grid constructor
void
InitializeGrid(Grid *grid) {
  vec3 vertices[GRID_HEIGHT][GRID_WIDTH];
  GLushort faces[GRID_FACES_LENGTH];
  GLuint size = sizeof(vertices);

  for (int i = 0; i < GRID_HEIGHT; ++i) {
    for (int j = 0; j < GRID_WIDTH; ++j) {
      vec3 *vertex = &vertices[i][j];
      vertex->x = (float) (j - 50) / GRID_DEPTH;
      vertex->y = 0;
      vertex->z = (float) (i - 50) / GRID_DEPTH;
    }
  }

  {
    int i = 0;

    // Horizontal grid lines
    for (int y = 0; y < GRID_WIDTH; ++y) {
      for (int x = 0; x < GRID_WIDTH - 1; ++x) {
        faces[i++] = y * GRID_WIDTH + x;
        faces[i++] = y * GRID_WIDTH + x + 1;
      }
    }

    // Vertical grid lines
    for (int x = 0; x < GRID_WIDTH; ++x) {
      for (int y = 0; y < GRID_WIDTH - 1; ++y) {
        faces[i++] = y * GRID_WIDTH + x;
        faces[i++] = (y + 1) * GRID_WIDTH + x;
      }
    }
  }

  grid->position = vec3(0, 0, 0);
  grid->scale = vec3(1, 1, 1);

  GlisyVAOAttribute vPosition = {
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

  glisyUniformInit(&grid->model, "model", GLISY_UNIFORM_MATRIX, 4);
  glisyGeometryInit(&grid->geometry);
  glisyGeometryAttr(&grid->geometry, "position", &vPosition);
  glisyGeometryFaces(&grid->geometry,
                     GL_UNSIGNED_SHORT,
                     GRID_FACES_LENGTH,
                     faces);

  glisyGeometryUpdate(&grid->geometry);
  UpdateGrid(grid);
}

void
UpdateGrid(Grid *grid) {
  mat4 model = mat4_identity(mat4());

  model = mat4_translate(model, grid->position);
  model = mat4_scale(model, grid->scale);

  glisyUniformSet(&grid->model, &model, sizeof(model));
  glisyUniformBind(&grid->model, &program);
}

void
DrawGrid(Grid *grid) {
  UpdateGrid(grid);
  glisyGeometryBind(&grid->geometry, 0);
  glisyGeometryDraw(&grid->geometry, GL_LINES, 0, GRID_FACES_LENGTH);
  glisyGeometryUnbind(&grid->geometry);
}

static void
onMouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
  fov += yoffset;
  fov = min(MAX_FOV, max(fov, MIN_FOV));
}

int
main(void) {

  // init gl
  GLFW_SHELL_CONTEXT_INIT(3, 2);
  GLFW_SHELL_WINDOW_INIT(window, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetScrollCallback(window, onMouseScroll);
  glfwSetWindowUserPointer(window, &camera);

  // create shader program
  program = CreateProgram("grid.v.glsl", "grid.f.glsl");

  // init objects
  InitializeGrid(&grid);
  grid.scale = vec3(32, 32, 32);

  // bind current shader program
  glisyProgramBind(&program);

  // configure camera
  glisyCameraInitialize(&camera);
  transform = mat4_identity(mat4());
  camera.position = vec3(0, 0.5, -1);
  UpdateCamera(&camera, &program, transform, fov, aspect, near, far);

  // render loop
  GLFW_SHELL_RENDER(window, {
    glEnable(GL_DEPTH_TEST);

    const float time = glfwGetTime();
    const float angle = time * 5.0f;
    const float radians = dtor(angle);
    const vec3 rotation = vec3(0, 1, 0);
    (void) mat4_rotate(transform, radians, rotation);

    aspect = (float) width / (float) height;

    UpdateCamera(&camera, &program, transform, fov, aspect, near, far);
    DrawGrid(&grid);
  });

  return 0;
}
