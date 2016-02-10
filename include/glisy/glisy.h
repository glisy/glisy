#ifndef GLISY_H
#define GLISY_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Glisy API.
 */

#include <glisy/gl.h>
#include <glisy/vao.h>
#include <glisy/math.h>
#include <glisy/scene.h>
#include <glisy/shader.h>
#include <glisy/buffer.h>
#include <glisy/program.h>
#include <glisy/renderer.h>

/**
 * Cameras.
 */

#include <glisy/camera/perspective.h>

/**
 * Initialize Glisy.
 */

GLboolean
glisy_init(void);

/**
 * Terminate Glisy.
 */

GLboolean
glisy_terminate(void);

/**
 * Renders a Glisy Scene with a Glisy Camera.
 */

void
glisy_render(const glisy_renderer renderer,
             const glisy_scene scene,
             const glisy_perspective_camera camera);

#ifdef __cplusplus
}
#endif

#endif
