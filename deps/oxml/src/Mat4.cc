
#include <oxml/Mat4.h>

namespace oxml {

  Mat4::Mat4() {
    for (int i = 0; i < 16; ++i) {
      m[i] = 0.0f;
    }
  }

  Mat4::Mat4(float *values) {
    for (int i = 0; i < 16; ++i) {
      m[i] = values[i];
    }
  }

  Mat4::Mat4(float value) {
    for (int i = 0; i < 16; ++i) {
      m[i] = value;
    }
  }

  Mat4::Mat4(const Mat4& copy) {
    for (int i = 0; i < 16; ++i) {
      m[i] = copy.m[i];
    }
  }

  Mat4::~Mat4() {}

}