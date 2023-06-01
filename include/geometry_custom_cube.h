/**
*
 * @brief Custom cube header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#ifndef __GEOMETRY_CUSTOM_CUBE_H__
#define __GEOMETRY_CUSTOM_CUBE_H__ 1

#include "EDK3/geometry.h"
#include "EDK3/dev/buffer.h"

namespace EDK3 {

  /**
  * @class CubeCustom
  * @brief Represents a custom cube geometry derived from EDK3::Geometry.
  *
  * This class defines a custom cube geometry used for rendering.
  */
  class CubeCustom : public EDK3::Geometry {
  public:
  
    /**
    * @brief Default constructor.
    */
    CubeCustom();

    /**
    * @brief Initializes the custom cube geometry.
    *
    * @param cube_size The size of the cube (default: 1.0f).
    * @param is_packed Indicates if the cube is packed.
    * @param is_cube_map Indicates if the cube is a cube map.
    */
    void init(const float cube_size = 1.0f,
              const bool is_packed = false, bool is_cube_map = false);

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
    * @brief Renders the cube geometry.
    */
    virtual void render() const override;

  protected:
    virtual ~CubeCustom();

  private:
    CubeCustom(const CubeCustom&);
    //CubeCustom(CubeCustom&&);
    CubeCustom& operator=(const CubeCustom&);

    EDK3::ref_ptr<EDK3::dev::Buffer> elements_buffer;
    EDK3::ref_ptr<EDK3::dev::Buffer> order_buffer;
    bool is_cube_map_;
  };

} //EDK3

#endif //__GEOMETRY_CUSTOM_CUBE_H__