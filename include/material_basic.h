/**
 *
 * @brief Basic material header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 * 
 */


#ifndef __MATERIAL_BASIC_H__
#define __MATERIAL_BASIC_H__ 1

#include "ESAT/math.h"
#include "EDK3/ref_ptr.h"
#include "EDK3/material.h"
#include "EDK3/materialsettings.h"
#include "EDK3/dev/program.h"
#include "EDK3/dev/shader.h"


namespace EDK3 {

/**
 * @class MaterialBasic
 * @brief Represents a basic material derived from EDK3::Material.
 *
 * This class defines a basic material with properties such as color. It overrides several methods from the base Material class.
 */
class MaterialBasic : public EDK3::Material {
 public:
  /**
  * @brief Constructor de MaterialBasic.
  */
  MaterialBasic();

  /**
  * @brief Inicializa el material.
  */
  void init();

  virtual bool enable(const EDK3::MaterialSettings *mat) const override;
  virtual void setupCamera(const float projection[16], const float view[16]) const override;
  virtual void setupModel(const float model[16]) const override;

  virtual unsigned int num_attributes_required() const;
  virtual EDK3::Attribute attribute_at_index(const unsigned int attrib_idx) const;
  virtual EDK3::Type attribute_type_at_index(const unsigned int attrib_index) const;

  /**
   * @class MaterialBasicSettings
   * @brief Represents the settings for the MaterialBasic material.
   *
   * This class defines the settings for the MaterialBasic material, such as color.
   */
  class MaterialBasicSettings : public EDK3::MaterialSettings {
   public:
    MaterialBasicSettings() {
      memset(color_, 0, sizeof(color_));
    }
    void set_color(const float v[4]) { memcpy(color_, v, sizeof(color_)); }
    const float* color() const { return color_; }
   protected:
    virtual ~MaterialBasicSettings() {}
   private:
    MaterialBasicSettings(const MaterialBasicSettings& other) { 
      memcpy(color_, other.color_, sizeof(color_));
    }
    MaterialBasicSettings(MaterialBasicSettings&& other) {
      memcpy(color_, other.color_, sizeof(color_));
      memset(other.color_, 0, sizeof(color_));
    }
    MaterialBasicSettings& operator=(const MaterialBasicSettings& other) {
      memcpy(color_, other.color_, sizeof(color_));
      return *this;
    }
    float color_[4];
  }; //MaterialBasicSettings


 protected:
  virtual ~MaterialBasic();

 private:
  EDK3::ref_ptr<EDK3::dev::Program> program_;

  MaterialBasic(const MaterialBasic&);
  MaterialBasic(MaterialBasic&&);
  MaterialBasic& operator=(const MaterialBasic&);
};

} //EDK3

#endif //__MATERIAL_BASIC_H__
