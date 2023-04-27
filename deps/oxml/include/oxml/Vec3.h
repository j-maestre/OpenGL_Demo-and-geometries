/**
 * \file entity.h
 * \author Jose Maria Maestre Quiles <maestrequi@esat-alumni.com>
 * 
 */
#ifndef __OXML_VEC3_H__
#define __OXML_VEC3_H__ 1

#include <oxml/Vec2.h>

namespace oxml {

  class Vec3 {
   public:
    Vec3();
    Vec3(float value);
    Vec3(float x, float y, float z);
    Vec3(const Vec2& v, float z);
    Vec3(float *values);
    Vec3(const Vec3& other);
    ~Vec3();

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator+(float value) const;
    Vec3& operator+=(const Vec3& other);
    Vec3& operator+=(float value);
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator-(float value) const;
    Vec3 operator-();
    Vec3& operator-=(const Vec3& other);
    Vec3& operator-=(float value);
    bool operator==(const Vec3& other) const;
    bool operator!=(const Vec3& other) const;
    void operator=(const Vec3& other);
    void operator=(float value);
    Vec3 operator*(float value) const;
    Vec3& operator*=(float value);
    Vec3 operator/(float value) const;
    Vec3& operator/=(float value);
    float& operator[](int index);
    const float& operator[](int index) const;

    float Magnitude() const;
    Vec3 Normalized() const;
    void Normalize();
    float SqrMagnitude() const;
    void Scale(const Vec3& other);

    static Vec3 Lerp(const Vec3& a, const Vec3& b, float t);
    static Vec3 LerpUnclamped(const Vec3& a, const Vec3& b, float t);
    static float Dot(const Vec3& a, const Vec3& b);
    static float Angle(const Vec3& a, const Vec3& b);
    static Vec3 Cross(const Vec3& a,const Vec3& b);	
    static float Distance(const Vec3& a, const Vec3& b);
    static Vec3 Reflect(const Vec3& direction, const Vec3& normal);
    static bool Approximately(const Vec3& a, const Vec3& b, float tolerance);

    static const Vec3 up;
    static const Vec3 down;
    static const Vec3 right;
    static const Vec3 left;
    static const Vec3 forward;
    static const Vec3 back;
    static const Vec3 zero;
    static const Vec3 unit;

    float x;
    float y;
    float z;
  };

}

#include "inl/Vec3.inl"

#endif 
