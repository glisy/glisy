#ifndef GLISY_CAMERA_PERSPECTIVE_H
#define GLISY_CAMERA_PERSPECTIVE_H

typedef struct glisy_perspective_camera glisy_perspective_camera;
struct glisy_perspective_camera {

  /**
   * Vertical camera field of view in degrees.
   */

  double fov;

  /**
   * Aspect ratio to determine horizontal field of view.
   */

  double aspect;

  /**
   * Distance from near clipping plane.
   */

  double near;

  /**
   * Distance from far clipping plane.
   */

  double far;
};

#endif
