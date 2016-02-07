#ifndef GLISY_QUAT_H
#define GLISY_QUAT_H

/**
 * quat struct type.
 */

typedef struct quat quat;
struct quat { float x; float y; float z; float w; };

/**
 * quat initializers.
 */

#define quat_create() quat(0, 0, 0, 1)
#define quat(x, y, z, w) (quat) {x, y, z, w}

#endif
