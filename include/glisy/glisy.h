#ifndef GLISY_H
#define GLISY_H

#ifdef __cplusplus
extern "C" {
#endif

#define GLISY_EXPORT __attribute__((visibility("default")))

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
#include <glisy/geometry.h>
#include <glisy/renderer.h>

/**
 * Cameras.
 */

#include <glisy/camera/perspective.h>

#ifdef __cplusplus
}
#endif

#endif
