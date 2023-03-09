#ifndef __INCLUDE_EDK3_TEXTURE__
#define __INCLUDE_EDK3_TEXTURE__ 1

// ----------------------------------------------------------------------------
// Copyright (C) 2014 Jose L. Hidalgo 
// Camera Class.
// ----------------------------------------------------------------------------
//

#include "referenced.h"
#include "constants.h"

namespace EDK3 {

  class Texture : public virtual Referenced {
  public:

    enum Type {
      T_Invalid,
      T_1D,
      T_2D,
      T_3D,
      T_CUBEMAP
    };

    // Internal and External representation
    // Not all formats can be used for internal texture representation
    enum Format {
      F_None,
      F_R,
      F_RG,
      F_RGB,
      F_BGR,
      F_BGRA,
      F_RGBA,
      F_DEPTH,
      F_DEPTH32,
    };

    enum Filter {
      //valid for minification & magnification
      F_NEAREST,
      F_LINEAR,

      // valid ONLY for minification:
      // Chooses the mipmap that most closely matches the size of the pixel being textured
      // and uses the GL_NEAREST criterion (the texture element closest to the specified texture
      //  coordinates) to produce a texture value.
      F_NEAREST_MIPMAP_NEAREST,

      // valid ONLY for minification:
      // Chooses the mipmap that most closely matches the size of the pixel being textured
      // and uses the GL_LINEAR criterion (a weighted average of the four texture elements 
      // that are closest to the specified texture coordinates) to produce a texture value.
      F_LINEAR_MIPMAP_NEAREST,

      // valid ONLY for minification:
      // Chooses the two mipmaps that most closely match the size of the pixel being textured
      // and uses the GL_NEAREST criterion (the texture element closest to the specified texture
      // coordinates ) to produce a texture value from each mipmap. The final texture value is a
      // weighted average of those 
      F_NEAREST_MIPMAP_LINEAR,

      // valid ONLY for minification:
      // Chooses the two mipmaps that most closely match the size of the pixel being textured
      // and uses the GL_LINEAR criterion (a weighted average of the texture elements that are
      // closest to the specified texture coordinates) to produce a texture value from each mipmap.
      // The final texture value is a weighted average of those two values.
      F_LINEAR_MIPMAP_LINEAR,
    };

    enum Wrap {
      W_REPEAT,
      W_MIRRORED_REPEAT,
      W_CLAMP_TO_EDGE,
    };

    // Uploading Data to the texture ------------------

    virtual void set_data(
        const Format f, // DataFormat of *data
        const EDK3::Type t,   // DataType of each element of *data
        const void *data,   // the data itself
        unsigned int mipmap_LOD = 0) = 0; // The LOD to fill (mipmapping only)

    // use the texture in the given texture unit
    virtual void bind(unsigned int textUnit) const = 0;
    virtual unsigned int internal_id() const = 0;

    // Other functions to implement (all of them must be implemented)
    // Also, remember to call the parent function in order to set the value.
    virtual void set_min_filter(Filter f)  { min_filter_ = f; }
    virtual void set_mag_filter(Filter f)  { mag_filter_ = f; }
    virtual void set_wrap_s(Wrap c) { wrap_s_ = c; }
    virtual void set_wrap_t(Wrap c) { wrap_t_ = c; }
    virtual void set_wrap_r(Wrap c) { wrap_r_ = c; }
    virtual void generateMipmaps() const { /* needed to implement if filtering uses mipmapping */ }

    // -------------------------------------------------------------------
    void set_wrap(Wrap c) { set_wrap_s(c); set_wrap_t(c); set_wrap_r(c); }
    const Filter min_filter() const   { return min_filter_; }
    const Filter mag_filter() const   { return mag_filter_; }
    const Wrap wrap_s() const       { return wrap_s_; }
    const Wrap wrap_t() const       { return wrap_t_; }
    const Wrap wrap_r() const       { return wrap_r_; }
    const Type type() const           { return type_;   }
    const Format format() const       { return format_; }
    const unsigned int width() const  { return width_;  }
    const unsigned int height() const { return height_; }
    const unsigned int depth() const  { return depth_;  }
    // -------------------------------------------------------------------

    // Loads PNG, JPEG, TGA, BMP, PSD, GIF, HDR, PIC
    static bool Load(const char *filename, ref_ptr<Texture> *output_tex);

  protected:
    Texture() : type_(T_Invalid), format_(F_None), width_(0), height_(0), depth_(0) {}

    void init(Type t, Format internal_format, unsigned int width, unsigned int height = 1, unsigned int depth = 1) {
      type_ = t;
      format_ = internal_format;
      width_ = width;
      height_ = height;
      depth_ = depth;
    }
    
    /** Referenced requires virtual protected destructor */
    virtual ~Texture() {}

  private:
    Type type_;
    Format format_;
    unsigned int width_;
    unsigned int height_;
    unsigned int depth_;
    Filter min_filter_;
    Filter mag_filter_;
    Wrap  wrap_s_;
    Wrap  wrap_t_;
    Wrap  wrap_r_;

    Texture(const Texture&);
    Texture& operator=(const Texture&);
  };

} /* end of EDK3 Namespace */
#endif
