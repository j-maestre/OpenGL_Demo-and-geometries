#version 330

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;

out vec3 s_textureDir;

void main()
{
  s_textureDir = a_position;
  vec4 pos = u_projection_matrix * mat4(mat3(u_view_matrix)) * vec4(a_position, 1.0);
  gl_Position = pos.xyww;
}