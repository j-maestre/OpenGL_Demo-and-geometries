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

/**
 * @class SurfaceCustom
 * @brief Represents a custom surface geometry derived from EDK3::Geometry.
 *
 * This class defines a custom surface geometry used for rendering.
 */
class SurfaceCustom : public EDK3::Geometry {
 public:
  /**
   * @brief Default constructor.
   */
  SurfaceCustom();

  /**
   * @brief Initializes the custom surface geometry.
   *
   * @param surface_points The array of surface points.
   * @param num_heights The number of heights in the surface (default: 4).
   * @param num_revs The number of revolutions in the surface (default: 4).
   * @param inverted Indicates if the surface is inverted (default: false).
   */
  void init(const float* surface_points,
            const int num_heights = 4, const int num_revs = 4, bool inverted = false);

  /**
   * @brief Binds the specified attribute to the specified location.
   *
   * @param a The attribute to bind.
   * @param where_to_bind_attribute The location to bind the attribute.
   * @return True if the attribute is bound successfully, false otherwise.
   */
  virtual bool bindAttribute(const Attribute a,
                             unsigned int where_to_bind_attribute)
                             const override;

  /**
   * @brief Renders the surface geometry.
   */
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
