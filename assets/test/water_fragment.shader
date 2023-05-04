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
uniform vec3 u_camera_position;
uniform float u_time;
uniform DirLight u_dirLight;
uniform vec4 u_color;
//uniform PointLight u_pointLight[4];
//uniform SpotLight u_spotLight[4];

in vec2 s_uv;
in vec3 s_normal;
in vec3 s_fragPos;

//vec3 direction = vec3(0.0, 1.0, 0.0);
//vec3 diffuse = vec3(1.0, 0.5, 0.0);

vec3 CalculeDirLight(DirLight light, vec3 normal, vec3 viewDir) {

  /*---Difuse---*/
  float diff = max(dot(normal, light.dir), 0.0);
  vec3 diffuse = diff * light.diffuse_color * u_color.xyz;

  /*---Specular---*/

  vec3 reflectDir = normalize(reflect(-(light.dir), normalize(normal))  );
  float spec = pow(max(dot(normalize(viewDir), normalize(reflectDir)), 0.0), light.specular_shininess);
  vec3 specular = light.specular_strength * spec * light.specular_color * u_color.xyz;

  return (diffuse + specular);
}

vec3 CaluclePointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
  vec3 lightDir = normalize(light.pos - fragPos);

  /*---Diffuse---*/
  float diff = max(dot(normal, lightDir), 0.0);
  vec3 diffuse = light.diffuse_color * diff * u_color.xyz;

  /*---Specular---*/
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), light.specular_shininess);
  vec3 specular = (light.specular_strength * spec * light.specular_color) * u_color.xyz;

  /*---Attenuation---*/
  float distance = length(light.pos - fragPos);
  float attenuation = 1.0 / (light.constant_att + light.linear_att * distance + 
                            light.quadratic_att * (distance * distance));


  diffuse *= attenuation;
  specular *= attenuation;

  return (diffuse + specular);
}

vec3 CalculeSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos) 
{
  vec3 lightDir = normalize(light.pos - fragPos);
  float theta = dot(lightDir, normalize(-light.dir));

  vec3 diffuse = vec3(0.0);
  vec3 specular = vec3(0.0);

  if (theta > light.outer_cut_off)
  {
    /*---Diffuse---*/
    float diff = max(dot(normal, lightDir), 0.0);
    diffuse = light.diffuse_color * diff * u_color.xyz;
    /*---Specular---*/
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), light.specular_shininess);
    specular = (light.specular_strength * spec * light.specular_color * u_color.xyz);
    
    float distance = length(light.pos - fragPos);
    float attenuation = 1.0 / (light.constant_att + light.linear_att * distance + 
                              light.quadratic_att * (distance * distance));

    float epsilon = light.cutt_off - light.outer_cut_off;
    float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);

    diffuse *= attenuation;
    specular *= intensity;

    diffuse *= intensity;
    specular *= intensity;

  }
  return (diffuse + specular);
}

void main() { 
  vec3 view_direction = normalize(u_camera_position - s_fragPos);

  float ambient_strength = 0.1;
  vec3 ambient_color = vec3(1.0);
  vec3 ambient = ambient_strength * ambient_color;

  vec3 color = ambient;

  color += CalculeDirLight(u_dirLight, s_normal, view_direction);

  fragColor = vec4(color, 0.5);
}
