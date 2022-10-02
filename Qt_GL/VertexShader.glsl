attribute vec3 vertex;
attribute vec3 color;

uniform mat4 projection;
uniform mat4 model_view;

varying vec3 my_color;

void main()
{
  gl_Position = projection * model_view * vec4(vertex, 1.0);
  my_color = color;
}
