/**
 *
 * @brief Custom quad header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#ifndef __GEOMETRY_CUSTOM_QUAD_H__
#define __GEOMETRY_CUSTOM_QUAD_H__ 1

#include "EDK3/geometry.h"
#include "EDK3/dev/buffer.h"

namespace EDK3 {

class QuadCustom : public EDK3::Geometry {
 public:
  QuadCustom();

  void init(const float quad_size = 1.0f);
  virtual bool bindAttribute(const Attribute a,
                             unsigned int where_to_bind_attribute) const override;
  virtual void render() const override;

 protected:
  virtual ~QuadCustom();

 private:
  QuadCustom(const QuadCustom&);
  //QuadCustom(QuadCustom&&);
  QuadCustom& operator=(const QuadCustom&);

  EDK3::ref_ptr<EDK3::dev::Buffer> elements_buffer;
  EDK3::ref_ptr<EDK3::dev::Buffer> order_buffer;
  bool is_initialized_;
};

} //EDK3

#endif //__GEOMETRY_CUSTOM_QUAD_H__
