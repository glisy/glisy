#version 400

precision mediump float;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

in vec3 position;

void main(void) {
  gl_Position = projection * view * model * vec4(position, 1.0);
}
