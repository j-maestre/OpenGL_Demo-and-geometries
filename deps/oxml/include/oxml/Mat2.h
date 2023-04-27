//--------------------------------------------------------------//
//  Math Library
//  Matrix 2 Class Definition.
//--------------------------------------------------------------//
//
//   m0 m1
//   m2 m3
//
//--------------------------------------------------------------//

/**
 * \file entity.h
 * \author Jose Maria Maestre Quiles <maestrequi@esat-alumni.com>
 * 
 */

#ifndef __MAT2_H__
#define __MAT2_H__ 1

#include <oxml/Vec2.h>

namespace oxml {

  class Mat2 {
  public:

    Mat2();
    Mat2(float *values);
    Mat2(float value);
    Mat2(const Vec2& a, const Vec2& b); 
    Mat2(const Mat2& copy);
    ~Mat2();

    static Mat2 Identity();
    
    Mat2 Multiply(const Mat2& other) const;
    float Determinant() const;
    Mat2 Adjoint() const;
    Vec2 GetLine(int line) const;
    Vec2 GetColum(int line) const;

    Mat2 Inverse() const;
    Mat2 Transpose() const;

    inline Mat2 operator+(const Mat2& other) const;
    inline void operator+=(const Mat2& other);
    inline Mat2 operator+(float value) const;
    inline void operator+=(float value);
    inline Mat2 operator-(const Mat2& other) const;
    inline void operator-=(const Mat2& other);
    inline Mat2 operator-(float value) const;
    inline void operator-=(float value);

    inline Mat2 operator*(float value) const;
    inline void operator*=(float value);
    inline Mat2 operator/(float value) const;
    inline void operator/=(float value);

    bool operator==(const Mat2& other) const;
    bool operator!=(const Mat2& other) const;
    inline void operator=(const Mat2& other);

    float m[4];
  };

}

#include "inl/Mat2.inl"

#endif
