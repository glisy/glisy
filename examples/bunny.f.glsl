#version 400

precision mediump float;

in vec3 color;
out vec4 fragColor;

void main(void) {
  fragColor = vec4(color, 1);
}
