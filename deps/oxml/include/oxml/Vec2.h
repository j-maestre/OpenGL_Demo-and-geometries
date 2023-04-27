/**
 * \file entity.h
 * \author Jose Maria Maestre Quiles <maestrequi@esat-alumni.com>
 * 
 */
#ifndef __OXML_VEC2_H__
#define __OXML_VEC2_H__ 1

namespace oxml {
  
  class Vec2 {
   public:

    Vec2();
    Vec2(float value);
    Vec2(float x, float y);
    Vec2(float *values);
    Vec2(const Vec2& copy);
    ~Vec2();
 
    Vec2 operator+(const Vec2& other) const;
    Vec2 operator+(float value) const;
    Vec2& operator+=(const Vec2& other);
    Vec2& operator+=(float value);
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator-(float value) const;
    Vec2 operator-() const;
    Vec2& operator-=(const Vec2& other);
    Vec2& operator-=(float value);
    bool operator==(const Vec2& other) const;
    bool operator!=(const Vec2& other) const;
    void operator=(const Vec2& other);
    void operator=(float value);
    Vec2 operator*(float value) const;
    Vec2& operator*=(float value);
    Vec2 operator/(float value) const;
    Vec2& operator/=(float value);
    float& operator[](int index);
    const float& operator[](int index) const;

    float Magnitude() const;
    float SqrMagnitude() const;
    void Normalize(); 
    Vec2 Normalized() const; 
    void Scale(const Vec2& scale); 

    static float Distance(const Vec2& a, const Vec2& b); 

    static float Dot(const Vec2& a,const Vec2& b);
    static Vec2 Lerp(const Vec2& a, const Vec2& b, float t);
    static Vec2 LerpUnclamped(const Vec2& a, const Vec2& b, float t);
    static bool Approximately(const Vec2& a, const Vec2& b, float tolerance);

    static const Vec2 up;
    static const Vec2 down;
    static const Vec2 right;
    static const Vec2 left;
    static const Vec2 zero;
    static const Vec2 one;

    float x;
    float y;
  };

}

#include "inl/Vec2.inl"

#endif // !__OXML_VEC2_H__
