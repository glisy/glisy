#ifndef GLISY_TEST_H
#define GLISY_TEST_H

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <GLFW/glfw3.h>

#define EPISILON 0.0001
#define fcmp(a, b) fabs(a - b) < EPISILON

#define TEST(body) { \
  if (!glfwInit()) return 1; \
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); \
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); \
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); \
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); \
  GLFWwindow *window = glfwCreateWindow(320, 320, "test", 0, 0); \
  if (!window) { return glfwTerminate(), 1; } \
  glfwMakeContextCurrent(window); \
  while (!glfwWindowShouldClose(window)) { \
    int width, height; \
    glfwGetFramebufferSize(window, &width, &height); \
    glViewport(0, 0, width, height); \
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); \
    glClear(GL_COLOR_BUFFER_BIT); \
    ({ body; }); \
    glDrawArrays(GL_TRIANGLES, 0, 3); \
    glfwSwapBuffers(window); \
    glfwPollEvents(); \
  } \
  glfwTerminate(); \
} \

#endif
