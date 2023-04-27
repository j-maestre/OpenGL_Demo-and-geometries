/**
 * \file camera.h
 * \author Hector Ochando <ochandoca@esat-alumni.com>
 * 
 */
#ifndef __MATHF_H__
#define __MATHF_H__ 1

namespace oxml {

  class Mathf {
  public:

    Mathf() = delete;
    
    static const float PI;
    static const float Epsilon;
    static const float Rad2Deg;
    static const float Deg2Rad;

    static float Abs(float value);
    static bool Approximately(float a, float b, float tolerance);
    static float Clamp(float value, float max, float min);
    static float Clamp01(float value);
    static float Pow(float value, float p);
    static float FloatModule(float a, float b);
    static float Round(float value);
    static float rsqrt(float number);

  };

}

#include "inl/Mathf.inl"

#endif