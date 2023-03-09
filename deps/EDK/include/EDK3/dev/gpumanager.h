// ----------------------------------------------------------------------------
// Copyright (C) 2014 Jose L. Hidalgo 
// GPUManager Class.
// ----------------------------------------------------------------------------

#ifndef INCLUDE_EDK3_GPUMANAGER_H_
#define INCLUDE_EDK3_GPUMANAGER_H_ 1

#include <EDK3/ref_ptr.h>
#include <EDK3/scoped_array.h>
#include <EDK3/referenced.h>
#include <EDK3/constants.h>
#include <EDK3/texture.h>

namespace EDK3 {
  class Engine;

namespace dev {

  class Shader;
  class Program;
  class Buffer;
  class Framebuffer;

  class GPUManager {
  public:
    // Singleton Pattern
    static GPUManager *Instance(); 

    // Replace GPU Manager Implementation
    // Must be done before creating the Window
    static void ReplaceGPUManagerImplementation(GPUManager *g);

    // Called by Engine once render context is set and ready to start drawing
    virtual void onStart() {}

    // Called by Engine once at before shuting down the render context
    virtual void onFinish() {}

    // 1st Implement buffer mechanism
    virtual void newBuffer(ref_ptr<Buffer> *output);
    // 2nd Implement Shader-Program-Uniforms
    virtual void newShader(ref_ptr<Shader> *output);
    virtual void newProgram(ref_ptr<Program> *output);

    virtual void newTexture1D(const Texture::Format internal_format, const unsigned int size, ref_ptr<Texture> *output);
    virtual void newTexture2D(const Texture::Format internal_format, const unsigned int width, const unsigned int height, ref_ptr<Texture> *output);
    virtual void newTexture3D(const Texture::Format internal_format, const unsigned int width, const unsigned int height, const unsigned int depth, ref_ptr<Texture> *output);

    enum FrameBufferElement {
      kFrameBufferColor   = 1 << 0,
      kFrameBufferDepth   = 1 << 1,
      kFrameBufferStencil = 1 << 2,
    };

    virtual void clearFrameBuffer(
        const float rgba[4],
        const unsigned int FrameBufferOrMask = 
            kFrameBufferColor | kFrameBufferDepth);

    virtual void enableVertexAttribute(
        const Buffer *buffer,
        const unsigned int attribute_index,
        const Type type,
        const bool normalized = false,
        const unsigned int offset = 0, 
        const unsigned int stride = 0);

    virtual void disableVertexAttribute(const unsigned int attrib_index);

    enum DrawMode {
      kDrawMode_Triangles,
      kDrawMode_TriangleStrip,
      kDrawMode_Points,
      kDrawMode_Lines,
      kDrawMode_LineStrip,
      kDrawMode_LineLoop
    };

    virtual void drawElements(
        const DrawMode mode, 
        unsigned int count,
        const Buffer *buffer,
        const Type element_type = T_USHORT,
        const unsigned int offset = 0) const;

    enum CompareFunc {
      kCompareFunc_Never,          // false -> always fails
      kCompareFunc_Less,           // a < b
      kCompareFunc_LessOrEqual,    // a <= b
      kCompareFunc_Equal,          // a == b
      kCompareFunc_NotEqual,       // a != b
      kCompareFunc_GreaterOrEqual, // a >= b
      kCompareFunc_Greater,        // a > b
      kCompareFunc_Always          // true -> always passes
    };

    virtual void enableDepthTest(const CompareFunc f);
    virtual void disableDepthTest();

    enum BlendParam {
      kBlendParam_Zero,
      kBlendParam_One,
      kBlendParam_SourceColor,
      kBlendParam_OneMinusSourceColor,
      kBlendParam_DestinationColor,
      kBlendParam_OneMinusDestinationColor,
      kBlendParam_SourceAlpha,
      kBlendParam_OneMinusSourceAlpha,
      kBlendParam_DestinationAlpha,
      kBlendParam_OneMinusDestinationAlpha,
      kBlendParam_ConstantColor,
      kBlendParam_OneMinusConstantColor,
      kBlendParam_ConstantAlpha,
      kBlendParam_OneMinusConstantAlpha,
      kBlendParam_SourceAlphaSaturate,
    };

    enum BlendOp {
      kBlendOp_Add,
      kBlendOp_Subtract,
      kBlendOp_ReverseSubtract,
      kBlendOp_Min,
      kBlendOp_Max,
    };

    virtual void enableBlend(BlendParam source, BlendParam destination, BlendOp operation, const float ConstantColor[4]);
    void disableBlend();
    

    enum FaceType {
      kFace_Back,
      kFace_Front,
      kFace_FrontAndBack
    };

    virtual void enableCullFaces(const FaceType f);
    virtual void disableCullFaces();

    virtual void enableScissor(
        int x, int y,
        unsigned int width,
        unsigned int height);
    virtual void disableScissor();

    virtual void changeColorMask(
        const bool red = true,
        const bool green = true,
        const bool blue = true,
        const bool alpha = true);
    virtual void changeDepthMask(bool enable = true);

    virtual void newFramebuffer(ref_ptr<Framebuffer> *output);
    virtual void bindDefaultFramebuffer();

    virtual void saveState(scoped_array<char> *output);
    virtual void restoreState(const void *mem_block);

    static void CheckGLError(const char *msg = 0L);
    static void EnableCheckGLError(bool v);

    // Called by window manager when gpu-manager needs to be initialized
    // Do not call manually.
    void doOnStart();
    void doOnFinish();
  protected:
    GPUManager();
    virtual ~GPUManager();

  private:
    GPUManager(const GPUManager&);
    GPUManager& operator=(const GPUManager&);
    static GPUManager *default_;
  };


}} /* end of EDK3::dev Namespace */

#endif
