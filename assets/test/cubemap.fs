#version 330
 
layout(location = 0) out vec4 fragColor;

uniform samplerCube u_cube_map_texture;

in vec3 s_textureDir;

void main()
{
  fragColor = texture(u_cube_map_texture, s_textureDir);
  //fragColor = vec4(s_textureDir, 1.0);
}