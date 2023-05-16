
#ifndef __MATERIAL_CUSTOM_H__
#define __MATERIAL_CUSTOM_H__ 1

#include "ESAT/math.h"
#include "EDK3/ref_ptr.h"
#include "EDK3/material.h"
#include "EDK3/materialsettings.h"
#include "EDK3/dev/program.h"
#include "EDK3/dev/shader.h"
#include "EDK3/texture.h"
#include "Lights.h"

namespace EDK3 {

  class MaterialCustom : public EDK3::Material {
  public:
    MaterialCustom();
    void init(const char* vertex_path, const char* fragment_path);

    virtual bool enable(const EDK3::MaterialSettings *mat) const override;
    virtual void setupCamera(const float projection[16], const float view[16]) const override;
    virtual void setupModel(const float model[16]) const override;

    virtual unsigned int num_attributes_required() const;
    virtual EDK3::Attribute attribute_at_index(const unsigned int attrib_idx) const;
    virtual EDK3::Type attribute_type_at_index(const unsigned int attrib_index) const;


    class MaterialCustomSettings : public EDK3::MaterialSettings {
    public:
      MaterialCustomSettings() {
        memset(color_, 0, sizeof(color_));
      }
      void set_color(const float v[4]) { memcpy(color_, v, sizeof(color_)); }
      const float* color() const { return color_; }

      void set_dir_light(ref_ptr<DirLight> dirLight) {dirLight_ = dirLight;}
      void set_point_light(ref_ptr<PointLight> point) {pointLight_ = point;}
      void set_spot_light(ref_ptr<SpotLight> spot) {spotLight_ = spot;}

      void set_camera_position(const float *pos) {cam_pos_ = pos;}
      const float* get_cam_pos() const {return cam_pos_;}

      const ref_ptr<DirLight> dir_light() const { return dirLight_;}
      const ref_ptr<PointLight> point_light() const { return pointLight_;}
      const ref_ptr<SpotLight> spot_light() const { return spotLight_;}

      void set_diffuse_texture(ref_ptr<Texture> texture) {diffuse_ = texture;}
      void set_specular_texture(ref_ptr<Texture> texture) {specular_ = texture;}
      ref_ptr<Texture> get_diffuse_texture() const {return diffuse_;}
      ref_ptr<Texture> get_specular_texture() const {return specular_;}
      void setResolution(float x, float y){resolutionX_ = x;resolutionY_ = y;};
      float getResolutionX() const {return resolutionX_;};
      float getResolutionY() const {return resolutionY_;};
    protected:
      virtual ~MaterialCustomSettings() {}
    private:
      MaterialCustomSettings(const MaterialCustomSettings& other) { 
        memcpy(color_, other.color_, sizeof(color_));
      }
      MaterialCustomSettings(MaterialCustomSettings&& other) {
        memcpy(color_, other.color_, sizeof(color_));
        memset(other.color_, 0, sizeof(color_));
      }
      MaterialCustomSettings& operator=(const MaterialCustomSettings& other) {
        memcpy(color_, other.color_, sizeof(color_));
        return *this;
      }
      float color_[4];
      const float *cam_pos_;
      ref_ptr<Texture> diffuse_;
      ref_ptr<Texture> specular_;
      ref_ptr<DirLight> dirLight_;
      ref_ptr<PointLight> pointLight_;
      ref_ptr<SpotLight> spotLight_;
      float resolutionX_;
      float resolutionY_;
    }; //MaterialBasicSettings


    protected:
    virtual ~MaterialCustom();

  private:
    EDK3::ref_ptr<EDK3::dev::Program> program_;

    MaterialCustom(const MaterialCustom&);
    MaterialCustom(MaterialCustom&&);
    MaterialCustom& operator=(const MaterialCustom&);
  };

} //EDK3

#endif