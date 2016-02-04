#ifndef GLISY_CONTEXT_H
#define GLISY_CONTEXT_H

#include <glisy/program.h>

/**
 * glisy context structure.
 */

typedef struct glisy_context glisy_context;
struct glisy_context {

  /**
   * glisy program interface.
   */

  glisy_program program;

  /**
   * Optional program name.
   */

  const char *name;

  /**
   * User data.
   */

  void *data;
};

/**
 * Initializes a glisy context.
 */

void
glisy_context_init (glisy_context *);

/**
 * Sets user data pointer.
 */

void
glisy_context_use (glisy_context *, const void *);

/**
 * Predicate to determine if context should update.
 * Returns 1 if true, otherwise 0.
 */

int
glisy_context_should_update (glisy_context *);

#endif
