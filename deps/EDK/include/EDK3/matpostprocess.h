#ifndef INCLUDE_EDK3_MAT_POSTPROCESS_H_
#define INCLUDE_EDK3_MAT_POSTPROCESS_H_ 1

// ----------------------------------------------------------------------------
// Copyright (C) 2015 Jose L. Hidalgo 
// Example of a post-processing material
// ----------------------------------------------------------------------------

#include "ref_ptr.h"
#include "material.h"
#include "materialsettings.h"
#include "texture.h"
#include "dev/program.h"

namespace EDK3 {

  class MatPostprocess : public Material {
  public:
    MatPostprocess();
    virtual bool enable(const MaterialSettings *) const;
    virtual void setupCamera(const float projecton[16], const float view[16]) const;
    virtual void setupModel(const float m[16]) const;

    unsigned int num_attributes_required() const;
    Attribute attribute_at_index(
        const unsigned int attrib_idx) const;
    Type attribute_type_at_index(
        const unsigned int attrib_index) const;

    class Blit: public MaterialSettings {
    public:
      Blit();
      void set_multiply_color(const float v[4]);
      void set_additive_color(const float v[4]);
      void set_texture(Texture *tex) { texture_ = tex; }
    protected:
      virtual ~Blit() {}
    private:
      Blit(const Blit&);
      Blit& operator=(const Blit&);
      float m_color_[4];
      float a_color_[4];
      ref_ptr<Texture> texture_;
      friend class MatPostprocess;
    };

    class Fade: public MaterialSettings {
    public:
      Fade() : progress_(0.0f) {}
      void set_textures(Texture *A, Texture *B) { texture_[0] = A; texture_[1] = B; }
      void set_progress(float f) { progress_ = f; }
    protected:
      virtual ~Fade() {}
    private:
      Fade(const Fade&);
      Fade& operator=(const Fade&);
      float progress_;
      ref_ptr<Texture> texture_[2];
      friend class MatPostprocess;
    };

    class Blur : public MaterialSettings {
    public:
      enum Direction {
        kHorizontal,
        kVertical,
      };
      Blur() :direction_(kHorizontal) {}
      void set_texture(Texture *t) { texture_ = t; }
      void set_direction(Direction d) { direction_ = d; }
    protected:
      virtual ~Blur() {}
    private:
      Blur(const Blur&);
      Blur& operator=(const Blur&);
      
      ref_ptr<Texture> texture_;
      Direction direction_;

      friend class MatPostprocess;
    };


  protected:
    virtual ~MatPostprocess() {}
  private:
    ref_ptr<dev::Program> program_;
    MatPostprocess(const MatPostprocess&);
    MatPostprocess& operator=(const MatPostprocess &);
  };

} /* end of EDK Namespace */

#endif
