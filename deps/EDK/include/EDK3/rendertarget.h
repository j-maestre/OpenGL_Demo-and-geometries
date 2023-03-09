#ifndef INCLUDE_EDK3_RENDER_TARGET_
#define INCLUDE_EDK3_RENDER_TARGET_ 1

#include "ref_ptr.h"
#include "scoped_ptr.h"
#include "texture.h"

// ----------------------------------------------------------------------------
// Copyright (C) 2015 Jose L. Hidalgo 
// Render Target
// ----------------------------------------------------------------------------

namespace EDK3 {

  class RenderTarget : public Referenced {
  public:
    RenderTarget();
    void init(unsigned int width, unsigned int height, unsigned int color_attachments = 1);
    const Texture* color_texture(unsigned int index = 0) const;
    const Texture* depth_texture() const;
    Texture* color_texture(unsigned int index = 0);
    Texture* depth_texture();
    // from now on, every draw-call will end up in the RenderTarget
    void begin() const;
    // finishes the rendering process inside the rendertarget
    void end() const;

    unsigned int width() const;
    unsigned int height() const;
    static RenderTarget* CurrentRenderTarget();
    struct Data;
  protected:
    virtual ~RenderTarget();
  private:
    RenderTarget(const RenderTarget&);
    RenderTarget& operator=(const RenderTarget &);
    scoped_ptr<Data> data_;
  };
}

#endif
