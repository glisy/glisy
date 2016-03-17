#ifndef GLISY_H
#define GLISY_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
  // Windows - set up dll import/export decorators.
# if defined(BUILDING_GLISY_SHARED)
    // Building shared library.
#   define GLISY_EXPORT __declspec(dllexport)
# elif defined(USING_GLISY_SHARED)
    // Using shared library.
#   define GLISY_EXPORT __declspec(dllimport)
# else
    // Building static library
#   define GLISY_EXPORT
# endif
#elif __GNUC__ >= 4
# define GLISY_EXPORT __attribute__((visibility("default")))
#else
  // nothing
# define GLISY_EXPORT
#endif

/**
 * Glisy API.
 */

#include <glisy/gl.h>
#include <glisy/vao.h>
#include <glisy/math.h>
#include <glisy/color.h>
#include <glisy/shader.h>
#include <glisy/buffer.h>
#include <glisy/uniform.h>
#include <glisy/program.h>
#include <glisy/geometry.h>

#ifdef __cplusplus
}
#endif

#endif
