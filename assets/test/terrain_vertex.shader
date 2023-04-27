#version 330

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;

out vec2 s_uv;
out vec3 s_normal;

void main()
{
  gl_Position = (u_projection_matrix * u_view_matrix * u_model_matrix) * vec4(a_position, 1.0);
  s_uv = a_uv;
  s_normal = mat3(u_model_matrix) * a_normal;
}
