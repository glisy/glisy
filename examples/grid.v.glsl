#version 400

uniform mat4 uProjection;
uniform mat4 uModel;
uniform mat4 uView;

in vec3 vPosition;

void
main(void) {
  gl_Position = uProjection * uModel * uView * vec4(vPosition, 1.0);
}
