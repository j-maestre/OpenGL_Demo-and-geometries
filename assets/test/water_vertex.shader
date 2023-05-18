#version 330

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;
uniform vec3 u_camera_position;
uniform float u_time;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;

out vec2 s_uv;
out vec3 s_normal;
out vec3 s_fragPos;


mat4 Identity(){
  mat4 identity = mat4(1.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 0.0, 1.0, 0.0,
                       0.0, 0.0, 0.0, 1.0);
  return identity;
}


//Example of function which returns a translation matrix:
mat4 InitAsTranslate(float tx, float ty, float tz) {
  return mat4(1.0, 0.0, 0.0, 0.0,
              0.0, 1.0, 0.0, 0.0,
              0.0, 0.0, 1.0, 0.0,
              tx,  ty,  tz,  1.0);
}


void main()
{

  vec4 uv = vec4(0.0);
  //mat4 translate = InitAsTranslate(0.00001, sin(u_time * 0.001) * 3.0, 0.0001);
  //mat4 translate = InitAsTranslate(0.00001, 0.0001, 0.0001);
  mat4 model = u_model_matrix;

  vec4 pos = model * vec4(a_position, 1.0);
  gl_Position = (u_projection_matrix * u_view_matrix) * (vec4(pos.x, 
                                                              pos.y + (sin(pos.x + (u_time * 0.001)) * 0.5),
                                                              pos.z + (cos(pos.x + u_time * 0.0005) * 6.0),
                                                              pos.w)); 

  //gl_Position = (u_projection_matrix * u_view_matrix * model) * vec4(a_position, 1.0);


  s_uv = a_uv;
  s_normal = mat3(model) * a_normal;


  s_fragPos = vec3(pos);
}
