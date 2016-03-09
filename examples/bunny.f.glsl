#version 400

precision mediump float;
in vec3 mColor;
out vec4 fragColor;

void
main(void) {
  fragColor = vec4(mColor, 1);
}
