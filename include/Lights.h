#ifndef __LIGHTS_H__
#define __LIGHTS_H__ 1

#include "EDK3/referenced.h"

class DirLight : public EDK3::Referenced
{
  public:
  float active;
  float dir[3];
  float diffuse_color[3];
  float specular_color[3];
  float specular_strength;
  float specular_shininess;
};

class PointLight : public EDK3::Referenced
{
  public:
  float active;
  float pos[3];
  float diffuse_color[3];
  float specular_color[3];
  float specular_strength;
  float specular_shininess;
  float constant_att;
  float linear_att;
  float quadratic_att;
};

class SpotLight : public EDK3::Referenced
{
  public:
  float active;
  float pos[3];
  float dir[3];
  float cutt_off;
  float outer_cut_off;
  float diffuse_color[3];
  float specular_color[3];
  float specular_strength;
  float specular_shininess;
  float constant_att;
  float linear_att;
  float quadratic_att;
};


#endif //__DIRECTIONAL_LIGHT_H__