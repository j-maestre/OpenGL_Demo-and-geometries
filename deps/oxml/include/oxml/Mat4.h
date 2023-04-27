/**
 * \file entity.h
 * \author Jose Maria Maestre Quiles <maestrequi@esat-alumni.com>
 * 
 */
#ifndef __OXML_MAT4_H__
#define __OXML_MAT4_H__ 1

#include <oxml/Vec3.h>
#include <oxml/Vec4.h>

namespace oxml {

  class Mat4 {
   public:

    Mat4();
    Mat4(float *values);
    Mat4(float value);
    Mat4(const Mat4& other);
    ~Mat4();

    static Mat4 Identity();
    Mat4 Multiply(const Mat4& other) const;

    float Determinant() const;
    Mat4 Adjoint() const;
    bool GetInverse(Mat4& out) const;
    bool Inverse();
    void SetTRS(const Vec3& translate, const Vec3& scale, const Vec3& rotation);

    Mat4 Transpose() const;

    static Mat4 Translate(const Vec3& position);
    static Mat4 Translate(float x, float y, float z);

    static Mat4 Scale(const Vec3& scale);
    static Mat4 Scale(float x, float y, float z);

    static Mat4 RotateX(float radians);
    static Mat4 RotateY(float radians);
    static Mat4 RotateZ(float radians);

    static Mat4 TRS(const Vec3& translate, const Vec3& scale, const Vec3& rotation);

    static Mat4 TRS(float trans_x, float trans_y, float trans_z,
                        float scale_x, float scale_y, float scale_Z,
                        float rotateX, float rotateY, float rotateZ);

    static Mat4 Perspective(float fov, float aspect,
      float near, float far);

    static Mat4 Ortho(float right, float left, float top, float valuebottom,
      float near, float far);

    static Mat4 LookAt(const Vec3& from, const Vec3& to, const Vec3& up);

    Vec4 GetColum(int colum) const;
    Vec4 GetRow(int line) const;

    Mat4 operator+(const Mat4& other) const;
    Mat4& operator+=(const Mat4& other);
    Mat4 operator+(float value) const;
    Mat4& operator+=(float value);
    Mat4 operator-(const Mat4& other) const;
    Mat4& operator-=(const Mat4& other);
    Mat4 operator-(float value) const;
    Mat4& operator-=(float value);
    Mat4& operator*=(float value);
    Mat4 operator*(float value) const;
    Vec4 operator*(const Vec4& vector) const;
    Mat4& operator/=(float value);
    Mat4 operator/(float value) const;
    bool operator==(const Mat4& other) const ;
    bool operator!=(const Mat4& other) const ;
    Mat4& operator=(const Mat4& other);

    float m[16];
  };

}

#include "inl/Mat4.inl"

#endif
