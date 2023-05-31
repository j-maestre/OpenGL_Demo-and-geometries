/**
 *
 * @brief Custom sphere header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#ifndef __GEOMETRY_CUSTOM_SPHERE_H__
#define __GEOMETRY_CUSTOM_SPHERE_H__ 1

#include "EDK3/geometry.h"
#include "EDK3/dev/buffer.h"

namespace EDK3 {

class SphereCustom : public EDK3::Geometry {
 public:
  SphereCustom();

  void init(bool *wireframe, const float sphere_size = 1.0f, const int num_heights = 20,
            const int num_revs = 20);
  virtual bool bindAttribute(const Attribute a,
                             unsigned int where_to_bind_attribute) const override;
  virtual void render() const override;

 protected:
  virtual ~SphereCustom();

 private:
  SphereCustom(const SphereCustom&);
  SphereCustom(SphereCustom&&);
  SphereCustom& operator=(const SphereCustom&);

  EDK3::ref_ptr<EDK3::dev::Buffer> elements_buffer_;
  EDK3::ref_ptr<EDK3::dev::Buffer> order_buffer_;
  bool is_initialized_;
  int num_heights_;
  int num_revs_;
  bool *wireFrameMode_;
};

} //EDK3

#endif //__GEOMETRY_CUSTOM_SPHERE_H__
