/**
 *
 * @brief Custom GPU Manager header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 * Look for OpenGL functions which name is close similar to these functions...
 * 
 */

#ifndef __CUSTOM_GPU_MANAGER_H__
#define __CUSTOM_GPU_MANAGER_H__ 1

#include <stdio.h>
#include "EDK3/dev/opengl.h"
#include "EDK3/dev/gpumanager.h"

namespace EDK3 {

namespace dev {

class CustomGPUManager : public EDK3::dev::GPUManager {
 public:
  virtual void newShader(EDK3::ref_ptr<EDK3::dev::Shader> *output) override;
  virtual void newProgram(EDK3::ref_ptr<EDK3::dev::Program> *output) override;
 
   
  virtual void newBuffer(EDK3::ref_ptr<EDK3::dev::Buffer> *output) override;
   
   
  virtual void newTexture1D(const Texture::Format internal_format, 
                            const unsigned int size,  
                            EDK3::ref_ptr<Texture>* output) override;
  virtual void newTexture2D(const Texture::Format internal_format, 
                            const unsigned int width, const unsigned int height, 
                            EDK3::ref_ptr<Texture>* output) override;
  virtual void newTexture3D(const Texture::Format internal_format, 
                            const unsigned int width, const unsigned int height, 
                            const unsigned int depth, 
                            EDK3::ref_ptr<Texture>* output) override;
   

   /*
  virtual void newFramebuffer(EDK3::ref_ptr<Framebuffer>* output) override;
  virtual void clearFrameBuffer(const float rgba[4],
                                const unsigned int FrameBufferOrMask =
                                kFrameBufferColor | kFrameBufferDepth) override;
   */

  
  virtual void enableDepthTest(const CompareFunc f) override;
  virtual void disableDepthTest() override;
   

   
  virtual void enableBlend(BlendParam source, 
                           BlendParam destination, 
                           BlendOp operation, 
                           const float ConstantColor[4]) override;
  void disableBlend();
   

   
  virtual void enableCullFaces(const FaceType f) override;
  virtual void disableCullFaces() override;
   

   
  virtual void enableScissor(int x, int y,
                             unsigned int width,
                             unsigned int height) override;
  virtual void disableScissor() override;
   

   
  virtual void enableVertexAttribute(const EDK3::dev::Buffer *buffer,
                                     const unsigned int attribute_index,
                                     const EDK3::Type type,
                                     const bool normalized = false,
                                     const unsigned int offset = 0,
                                     const unsigned int stride = 0) override;
   

   
  virtual void disableVertexAttribute(const unsigned int attrib_index) override;
   

   
  virtual void drawElements(const DrawMode mode,
                            unsigned int count,
                            const EDK3::dev::Buffer *buffer,
                            const EDK3::Type element_type = EDK3::Type::T_USHORT,
                            const unsigned int offset = 0) const override;
   

  void set_wireframe(bool wireframe);
private:
  bool wireframe_;
}; //CustomGPUManager

} //dev

} //EDK3

#endif //__CUSTOM_GPU_MANAGER__
