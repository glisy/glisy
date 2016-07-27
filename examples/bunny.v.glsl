#version 400

precision mediump float;

uniform mat4 projection;
uniform mat4 view;

in vec3 position;
out vec3 color;

void main(void) {
  color = vec3(position);
  gl_Position = projection * view * vec4(position, 1.0);
}
