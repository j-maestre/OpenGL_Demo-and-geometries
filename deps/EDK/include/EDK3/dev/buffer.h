#ifndef INCLUDE_EDK3_DEV_BUFFER_H_
#define INCLUDE_EDK3_DEV_BUFFER_H_ 1

#include <EDK3/referenced.h>
#include <EDK3/scoped_array.h>

namespace EDK3 {
namespace dev {

  /* OpenGL Calls used:
       glBindBuffer
       glBufferData
       glBufferSubData
       glDeleteBuffers
       glGenBuffers
  */
  class Buffer : public Referenced {
  public:
    enum Target {
      kTarget_Vertex_Data,
      kTarget_Elements,
    };
    virtual void init(unsigned int size) = 0;
    virtual void bind(const Target t) const = 0;
    virtual unsigned int size() const = 0;
    virtual void uploadData(
        const void *data, 
        unsigned int size, 
        unsigned int offset = 0) = 0;
    virtual void release() = 0;

  protected:
    Buffer() {}
    virtual ~Buffer() {}

  private:
    Buffer(const Buffer&);
    Buffer& operator=(const Buffer&);
  };

}} /* end of EDK3::dev Namespace */

#endif
