/* Copyright 2015 ESAT. All rights reserved.    #####  #####      #     #####
 * Author: Jose L. Hidalgo <jlhidalgo@esat.es>  #      #         # #      #
 *                                              ###     ###     #   #     #
 * Math reference methods                       #          #   #     #    #
 *                                              #####  #####  #       #   #
 */

#ifndef ESAT_MATH_H
#define ESAT_MATH_H 1

namespace ESAT {

  struct Vec2 { float x, y; };
  struct Vec3 { float x, y, z; };
  struct Vec4 { float x, y, z, w;  };
  
  struct Mat3 { float d[9]; };
  struct Mat4 { float d[16]; };

  Mat3 Mat3Multiply(const Mat3 &a, const Mat3 &b);
  Mat3 Mat3Identity();
  Mat3 Mat3Translate(float translate_x, float translate_y);
  Mat3 Mat3Rotate(float radians);
  Mat3 Mat3Scale(float scale_x, float scale_y);
  Mat3 Mat3FromColumns(const float data[9]);
  Vec3 Mat3TransformVec3(const Mat3 &a, const Vec3 &v);
  Vec2 Mat3TransformVec2(const Mat3 &a, const Vec2  &v);
  
  Mat4 Mat4Multiply(const Mat4 &a, const Mat4 &b);
  Mat4 Mat4Identity();
  Mat4 Mat4Translate(float translate_x, float translate_y, float translate_z);
  Mat4 Mat4RotateX(float radians);
  Mat4 Mat4RotateY(float radians);
  Mat4 Mat4RotateZ(float radians);
  Mat4 Mat4Scale(float scale_x, float scale_y, float scale_z);
  Mat4 Mat4FromColumns(const float data[16]);
  Mat4 Mat4Projection();
  Vec4 Mat4TransformVec4(const Mat4 &a, const Vec4 &v);
  Vec3 Mat4TransformVec3(const Mat4 &a, const Vec3 &v);

  void Mat3TransformRawVec2(const Mat3 &m, const float v_in[2], float v_out[2]);
  void Mat3TransformRawVec3(const Mat3 &m, const float v_in[3], float v_out[3]);
  void Mat4TransformRawVec3(const Mat4 &m, const float v_in[3], float v_out[3]);
  void Mat4TransformRawVec4(const Mat4 &m, const float v_in[4], float v_out[4]);


} /* ESAT */

#endif
