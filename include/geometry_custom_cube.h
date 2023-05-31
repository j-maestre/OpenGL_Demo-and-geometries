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

  class CubeCustom : public EDK3::Geometry {
  public:

    CubeCustom();

    void init(bool *wireframe, const float cube_size = 1.0f,
              const bool is_packed = false, bool is_cube_map = false);
    virtual bool bindAttribute(const Attribute a,
                               unsigned int where_to_bind_attribute) const override;
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
    bool *wireFrameMode_;
  };

} //EDK3

#endif //__GEOMETRY_CUSTOM_CUBE_H__