/**
 *
 * @brief Custom surface header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#ifndef __GEOMETRY_CUSTOM_SURFACE_H__
#define __GEOMETRY_CUSTOM_SURFACE_H__ 1

#include "EDK3/geometry.h"
#include "EDK3/dev/buffer.h"

namespace EDK3 {

class SurfaceCustom : public EDK3::Geometry {
 public:
  SurfaceCustom();

  void init(const float* surface_points,
            const int num_heights = 4, const int num_revs = 4);
  virtual bool bindAttribute(const Attribute a,
                             unsigned int where_to_bind_attribute)
                             const override;
  virtual void render() const override;

 protected:
  virtual ~SurfaceCustom();

 private:
  SurfaceCustom(const SurfaceCustom&);
  SurfaceCustom(SurfaceCustom&&);
  SurfaceCustom& operator=(const SurfaceCustom&);

  EDK3::ref_ptr<EDK3::dev::Buffer> elements_buffer;
  EDK3::ref_ptr<EDK3::dev::Buffer> order_buffer;
  bool is_initialized_;
  int num_heights_;
  int num_revs_;
};

} //EDK3

#endif //__GEOMETRY_CUSTOM_SURFACE_H__
