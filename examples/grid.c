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
  GlisyUniform uModel;
  mat4 translation;
  vec3 position;
};

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

  mat4_identity(grid->translation);

  glisyUniformInit(&grid->uModel,
                   "uModel",
                   GLISY_UNIFORM_MATRIX, 4);

  glisyGeometryInit(&grid->geometry);
  glisyGeometryAttr(&grid->geometry,
                    "vPosition",
                    &vPosition);

  glisyGeometryFaces(&grid->geometry,
                     GL_UNSIGNED_SHORT,
                     GRID_FACES_LENGTH,
                     faces);

  glisyGeometryUpdate(&grid->geometry);
  UpdateGrid(grid);
}

void
UpdateGrid(Grid *grid) {
  mat4 model;
  mat4 translation;

  mat4_identity(model);
  mat4_identity(translation);

  model = mat4_translate(translation, grid->position);
  model = mat4_multiply(model, translation);

  glisyUniformSet(&grid->uModel, &model, sizeof(model));
  glisyUniformBind(&grid->uModel, 0);
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
  GlisyProgram program;

  // objects
  Camera camera;
  Grid grid;

  // init gl
  GLFW_SHELL_CONTEXT_INIT(3, 2);
  GLFW_SHELL_WINDOW_INIT(window, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetScrollCallback(window, onMouseScroll);
  glfwSetWindowUserPointer(window, &camera);

  // create shader program
  program = CreateProgram("grid.v.glsl", "grid.f.glsl");

  // init objects
  InitializeCamera(&camera, WINDOW_WIDTH, WINDOW_HEIGHT);
  InitializeGrid(&grid);

  // configure camera
  camera.position = vec3(1, 1, 1);
  camera.fov = 22;

  // bind current shader program
  glisyProgramBind(&program);

  // render loop
  GLFW_SHELL_RENDER(window, {
    const float time = glfwGetTime();
    const float angle = time * 5.0f;
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
