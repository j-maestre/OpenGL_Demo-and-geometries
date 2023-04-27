#ifndef __OXML_VEC4_H__
#define __OXML_VEC4_H__ 1

#include <oxml/int.h>
#include <oxml/Vec3.h>

namespace oxml {

  class Vec4 {
   public:

    Vec4();
    Vec4(float x, float y, float z, float w);
    Vec4(const Vec3& v, float w);
    Vec4(float value);
    Vec4(float *values);
    Vec4(const Vec4& other);
    ~Vec4();
    
    Vec4 operator+(const Vec4& other) const;
    Vec4 operator+(float value) const;
    Vec4& operator+=(const Vec4& other);
    Vec4& operator+=(float value);
    Vec4 operator-(const Vec4& other) const;
    Vec4 operator-(float value) const;
    Vec4 operator-() const;
    Vec4& operator-=(const Vec4& other);
    Vec4& operator-=(float value);
    Vec4 operator*(float value) const;
    Vec4& operator*=(float value);
    Vec4 operator/(float value) const;
    Vec4& operator/=(float value);
    bool operator==(const Vec4& other);
    bool operator!=(const Vec4& other);
    Vec4& operator=(const Vec4& other);
    float& operator[](int index);
    const float& operator[](int index) const;

    float Magnitude() const;
    void Normalize();
    Vec4 Normalized() const;
    void Scale(const Vec4& scale);
    float SqrMagnitude() const;
    u32 ToRGBA() const;

    static float Distance(const Vec4& a, const Vec4& b);
    static float Dot(const Vec4& a, const Vec4& b);
    static Vec4 Lerp(const Vec4& a, const Vec4& b, float t);	
    static bool Approximately(const Vec4& a, const Vec4& b, float tolerance);

    static const Vec4 one;
    static const Vec4 zero;

    float x;
    float y;
    float z;
    float w;

  };

}

#include "inl/Vec4.inl"

#endif 
