#ifndef GLISY_H
#define GLISY_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * math.
 */

#include <glisy/math/vec2.h>
#include <glisy/math/vec3.h>
#include <glisy/math/vec4.h>
#include <glisy/math/mat2.h>
#include <glisy/math/mat3.h>
#include <glisy/math/mat4.h>
#include <glisy/math/quat.h>

/**
 * core.
 */

#include <glisy/gl.h>
#include <glisy/mesh.h>
#include <glisy/scene.h>
#include <glisy/shader.h>
#include <glisy/program.h>
#include <glisy/context.h>
#include <glisy/renderer.h>

/**
 * cameras.
 */

#include <glisy/camera/perspective.h>

/**
 * Initializes glisy. Returns 1 on success,
 * otherwise 0 on failure.
 */

int
glisy_init (void);

/**
 * Terminate glisy.
 */

void
glisy_terminate (void);

/**
 * Renders scene with camera.
 */

void
glisy_render (const glisy_renderer,
              const glisy_scene,
              const glisy_perspective_camera);

#ifdef __cplusplus
}
#endif
#endif
