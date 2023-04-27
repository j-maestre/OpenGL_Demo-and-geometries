#include <oxml/Vec4.h>

namespace oxml {

  const Vec4 Vec4::one = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
  const Vec4 Vec4::zero = Vec4(0.0f, 0.0f, 0.0f, 0.0f);

  Vec4::Vec4() { 
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
  }

  Vec4::Vec4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }

  Vec4::Vec4(const Vec3& v, float w) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = w;
  }

  Vec4::Vec4(float value) {
    x = value;
    y = value;
    z = value;
    w = value;
  }

  Vec4::Vec4(float* values) {
    x = values[0];
    y = values[1];
    z = values[2];
    w = values[3];
  }

  Vec4::Vec4(const Vec4& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
  }

  Vec4::~Vec4() { }

}