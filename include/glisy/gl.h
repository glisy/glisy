#ifndef GLISY_GL_H
#define GLISY_GL_H

#ifdef __APPLE__
#define __gl_h_
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#if __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif TARGET_IPHONE_SIMULATOR
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif TARGET_OS_MAC
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#else
#error Unsupported Apple platform
#endif
#elif __ANDROID__ || GLISY_USE_GLES2
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#endif
