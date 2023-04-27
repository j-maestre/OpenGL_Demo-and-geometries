#include <oxml/Vec3.h>

namespace oxml {

  const Vec3 Vec3::up = Vec3(0.0f, 1.0f, 0.0f);
  const Vec3 Vec3::down = Vec3(0.0f, -1.0f, 0.0f);
  const Vec3 Vec3::right = Vec3(1.0f, 0.0f, 0.0f);
  const Vec3 Vec3::left = Vec3(-1.0f, 0.0f, 0.0f);
  const Vec3 Vec3::forward = Vec3(0.0f, 0.0f, 1.0f);
  const Vec3 Vec3::back = Vec3(0.0f, 0.0f, -1.0f);
  const Vec3 Vec3::zero = Vec3(0.0f, 0.0f, 0.0f);
  const Vec3 Vec3::unit = Vec3(1.0f, 1.0f, 1.0f);

  Vec3::Vec3() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }

  Vec3::Vec3(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
  }

  Vec3::Vec3(float a) {
    x = a;
    y = a;
    z = a;
  }

  Vec3::Vec3(const Vec3& copy) {
    x = copy.x;
    y = copy.y;
    z = copy.z;
  }

  Vec3::Vec3(const Vec2& v, float z) {
   this->x = v.x;
   this->y = v.y;
   this->z = z;
  }

  Vec3::Vec3(float* values) {
    this->x = values[0];
    this->y = values[1];
    this->z = values[2];
  }

  Vec3::~Vec3() {}

}