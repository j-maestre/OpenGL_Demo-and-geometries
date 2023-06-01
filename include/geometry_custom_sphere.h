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

/**
 * @class SphereCustom
 * @brief Represents a custom sphere geometry derived from EDK3::Geometry.
 *
 * This class defines a custom sphere geometry used for rendering.
 */
class SphereCustom : public EDK3::Geometry {
 public:
   /**
   * @brief Default constructor.
   */
  SphereCustom();

  
  /**
   * @brief Initializes the custom sphere geometry.
   *
   * @param sphere_size The size of the sphere (default: 1.0f).
   * @param num_heights The number of heights in the sphere (default: 20).
   * @param num_revs The number of revolutions in the sphere (default: 20).
   */
  void init(const float sphere_size = 1.0f, const int num_heights = 20,
            const int num_revs = 20);

  /**
   * @brief Binds the specified attribute to the specified location.
   *
   * @param a The attribute to bind.
   * @param where_to_bind_attribute The location to bind the attribute.
   * @return True if the attribute is bound successfully, false otherwise.
   */
  virtual bool bindAttribute(const Attribute a,
                             unsigned int where_to_bind_attribute) const override;

  /**
   * @brief Renders the sphere geometry.
   */
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
};

} //EDK3

#endif //__GEOMETRY_CUSTOM_SPHERE_H__
