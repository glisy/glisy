#version 400

precision mediump float;
uniform mat4 uProjection;
uniform mat4 uView;

in vec3 vPosition;
out vec3 mColor;

void
main(void) {
  mColor = vec3(vPosition);
  gl_Position = uProjection * uView * vec4(vPosition, 1.0);
}
