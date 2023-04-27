#version 330

layout(location = 0) out vec4 fragColor;

struct DirLight
{
  float active;
  vec3 dir;
  vec3 diffuse_color;
  vec3 specular_color;
  float specular_strength;
  float specular_shininess;
};

struct PointLight
{
  float active;
  vec3 pos;
  vec3 diffuse_color;
  vec3 specular_color;
  float specular_strength;
  float specular_shininess;
  float constant_att;
  float linear_att;
  float quadratic_att;
};

struct SpotLight
{
  float active;
  vec3 pos;
  vec3 dir;
  float cutt_off;
  float outer_cut_off;
  vec3 diffuse_color;
  vec3 specular_color;
  float specular_strength;
  float specular_shininess;
  float constant_att;
  float linear_att;
  float quadratic_att;
};

uniform sampler2D u_diffuse_color;
uniform sampler2D u_specular_color;

uniform float u_time;
uniform DirLight u_dirLight;
//uniform PointLight u_pointLight[4];
//uniform SpotLight u_spotLight[4];

in vec2 s_uv;
in vec3 s_normal;

vec3 direction = vec3(0.0, 1.0, 0.0);
vec3 diffuse = vec3(1.0, 0.5, 0.0);

vec3 CalculeDirLight(DirLight light, vec3 normal, vec3 viewDir) {

  /*---Difuse---*/
  float diff = max(dot(normal, light.dir), 0.0);
  vec3 diffuse = diff * light.diffuse_color;

  /*---Specular---*/

  vec3 reflectDir = normalize(reflect(-(light.dir), normalize(normal))  );
  float spec = pow(max(dot(normalize(viewDir), normalize(reflectDir)), 0.0), light.specular_shininess);
  vec3 specular = light.specular_strength * spec * light.specular_color;

  return (diffuse + specular);
}

void main() {
  direction.x = cos(u_time * 0.001) + 0.5;
  float impacto = max(dot(s_normal, u_dirLight.dir), 0.0);
  vec3 diffuse = impacto * diffuse;


  //fragColor = vec4(s_normal, 1.0f);
  //fragColor = vec4(diffuse, 1.0);
  fragColor = vec4(u_dirLight.dir, 1.0);

}
