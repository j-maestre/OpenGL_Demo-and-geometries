/**
 *
 * @brief Basic postprocess material header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#ifndef __MATERIAL_POSTPROCESS_BASIC_H__
#define __MATERIAL_POSTPROCESS_BASIC_H__ 1

#include "ESAT/math.h"
#include "EDK3/ref_ptr.h"
#include "EDK3/material.h"
#include "EDK3/texture.h"
#include "EDK3/materialsettings.h"
#include "EDK3/dev/program.h"
#include "EDK3/dev/shader.h"


namespace EDK3 {
   
class PostprocessBasic : public EDK3::Material {
 public:
  PostprocessBasic();
  void init();

  virtual bool enable(const EDK3::MaterialSettings *mat) const override;
  virtual void setupCamera(const float projection[16], const float view[16]) const override;
  virtual void setupModel(const float model[16]) const override;

  virtual unsigned int num_attributes_required() const;
  virtual EDK3::Attribute attribute_at_index(const unsigned int attrib_idx) const;
  virtual EDK3::Type attribute_type_at_index(const unsigned int attrib_index) const;


  class PostprocessBasicSettings : public EDK3::MaterialSettings {
   public:
    PostprocessBasicSettings() {
      memset(color_, 0, sizeof(color_));
    }
    void set_color(const float v[4]) {
      memcpy(color_, v, sizeof(color_));
    }
    void set_texture(const EDK3::ref_ptr<EDK3::Texture> texture) {
      texture_ = texture;
    }
    const float* color() const {
      return color_;
    }
    const EDK3::ref_ptr<EDK3::Texture> texture() const {
      return texture_;
    }
   protected:
    virtual ~PostprocessBasicSettings() {}
   private:
    PostprocessBasicSettings(const PostprocessBasicSettings& other) {
      memcpy(color_, other.color_, sizeof(color_));
      texture_ = other.texture_;
    }
    PostprocessBasicSettings(PostprocessBasicSettings&& other) {
      memcpy(color_, other.color_, sizeof(color_));
      texture_ = other.texture_;
      memset(other.color_, 0, sizeof(color_));
      other.texture_.release();
    }
    PostprocessBasicSettings& operator=(const PostprocessBasicSettings& other) {
      memcpy(color_, other.color_, sizeof(color_));
      texture_ = other.texture_;
      return *this;
    }
    float color_[4];
    EDK3::ref_ptr<EDK3::Texture> texture_;
  }; //PostprocessBasicSettings


 protected:
  virtual ~PostprocessBasic();

 private:
  EDK3::ref_ptr<EDK3::dev::Program> program_;

  PostprocessBasic(const PostprocessBasic&);
  PostprocessBasic(PostprocessBasic&&);
  PostprocessBasic& operator=(const PostprocessBasic&);
};

} //EDK3

#endif //__MATERIAL_POSTPROCESS_BASIC_H__
