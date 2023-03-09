#ifndef INCLUDE_EDK3_MAT_DIFFUSE_TEXTURE_H_
#define INCLUDE_EDK3_MAT_DIFFUSE_TEXTURE_H_ 1

// ----------------------------------------------------------------------------
// Copyright (C) 2014 Jose L. Hidalgo 
// Diffuse Material Implementation
// ----------------------------------------------------------------------------

#include "ref_ptr.h"
#include "material.h"
#include "materialsettings.h"
#include "texture.h"
#include "dev/program.h"

namespace EDK3 {

  class MatDiffuseTexture : public Material {
  public:
    MatDiffuseTexture();
    virtual bool enable(const MaterialSettings *) const;
    virtual void setupCamera(const float projecton[16], const float view[16]) const;
    virtual void setupModel(const float m[16]) const;

    virtual unsigned int num_attributes_required() const;
    virtual Attribute attribute_at_index(
        const unsigned int attrib_idx) const;
    virtual Type attribute_type_at_index(
        const unsigned int attrib_index) const;

    class Settings : public MaterialSettings {
    public:
      Settings() { for (int i = 0; i < 4; ++i) data_[i] = 1.0f; }
      void set_color(const float v[4]) { memcpy(data_, v, sizeof(data_)); }
      void set_color(float r, float g, float b, float a = 1.0f) {
        data_[0] = r; data_[1] = g; data_[2] = b; data_[3] = a;
      }
     
      const float *color() const { return data_; }
      void set_texture(Texture *tex) { texture_ = tex; }
      Texture* texture() { return texture_.get(); }
      const Texture* texture() const { return texture_.get(); }
    protected:
      virtual ~Settings() {}
    private:
      Settings(const Settings&);
      Settings& operator=(const Settings&);
      float data_[4];
      ref_ptr<Texture> texture_;
    };

  protected:
    virtual ~MatDiffuseTexture() {}
  private:
    ref_ptr<dev::Program> program_;
    MatDiffuseTexture(const MatDiffuseTexture&);
    MatDiffuseTexture& operator=(const MatDiffuseTexture &);
  };

} /* end of EDK Namespace */

#endif
