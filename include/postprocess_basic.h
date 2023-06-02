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
   
/**
 * @class PostprocessBasic
 * @brief Clase que representa un procesamiento posterior básico.
 *
 * Esta clase hereda de EDK3::Material y se utiliza para realizar diferentes tipos de procesamiento posterior en una escena.
 */
class PostprocessBasic : public EDK3::Material {

 public:
  /**
   * @enum PostProcessType
   * @brief Enumeración que define los tipos de procesamiento posterior disponibles.
   *
   * Los tipos de procesamiento posterior incluyen Default, Color, GrayScale, Sepia, NightVision, InvertedColors y EdgeDetection.
   */
  enum PostProcessType{
    Default,
    Color,
    GrayScale,
    Sepia,
    NightVision,
    InvertedColors,
    EdgeDetection,
  };

  /**
   * @brief Constructor de PostprocessBasic.
   */
  PostprocessBasic();

  /**
   * @brief Inicializa el procesamiento posterior.
   * @param type Tipo de procesamiento posterior a inicializar. Por defecto es Default.
   */
  void init(PostProcessType = Default);

  /**
  * @brief Enables the cube map material with the specified settings.
  *
  * @param mat The material settings.
  * @return True if the material is enabled successfully, false otherwise.
  */
  virtual bool enable(const EDK3::MaterialSettings *mat) const override;

  /**
  * @brief Sets up the camera for rendering.
  *
  * @param projection The projection matrix.
  * @param view The view matrix.
  */
  virtual void setupCamera(const float projection[16], const float view[16]) const override;

  /**
  * @brief Sets up the model for rendering.
  *
  * @param model The model matrix.
  */
  virtual void setupModel(const float model[16]) const override;

  /**
  * @brief Returns the number of attributes required by the material.
  *
  * @return The number of required attributes.
  */
  virtual unsigned int num_attributes_required() const;

  /**
  * @brief Returns the attribute at the specified index.
  *
  * @param attrib_idx The attribute index.
  * @return The attribute at the specified index.
  */
  virtual EDK3::Attribute attribute_at_index(const unsigned int attrib_idx) const;

  /**
  * @brief Returns the type of the attribute at the specified index.
  *
  * @param attrib_index The attribute index.
  * @return The type of the attribute at the specified index.
  */
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
