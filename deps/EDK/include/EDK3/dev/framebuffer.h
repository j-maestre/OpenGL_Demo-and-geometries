#ifndef INCLUDE_EDK3_DEV_FRAMEBUFFER_H_
#define INCLUDE_EDK3_DEV_FRAMEBUFFER_H_ 1

#include <EDK3/referenced.h>
#include <EDK3/ref_ptr.h>
#include <EDK3/constants.h>

namespace EDK3 {
  class Texture;

namespace dev {
  class Framebuffer : public virtual Referenced {
  public:
    static unsigned int const MAX_COLOR_ATTACHMENTS = 16;
    virtual void attachColorTexture(Texture *, unsigned int attachment_pos) = 0;
    virtual void attachDepthTexture(Texture *) = 0;
    virtual bool bind() const = 0;
  protected:
    Framebuffer() {}
    ~Framebuffer() {}
  private:
    Framebuffer(const Framebuffer &);
    Framebuffer& operator=(const Framebuffer&);
  };

}} // EDK3::dev

#endif