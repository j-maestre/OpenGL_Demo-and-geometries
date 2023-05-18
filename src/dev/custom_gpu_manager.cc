#include "dev/custom_gpu_manager.h"

#include "custom_gpu_texture.h"
#include "EDK3/dev/glew.h"
#include "dev/custom_gpu_shader.h"
#include "dev/custom_gpu_program.h"
#include "dev/custom_gpu_buffer.h"

namespace EDK3
{
  
  namespace dev
  {

    void CustomGPUManager::newShader(EDK3::ref_ptr<EDK3::dev::Shader>* output)
    {
      output->allocT<CustomGPUShader>();
    }

    void CustomGPUManager::newProgram(EDK3::ref_ptr<EDK3::dev::Program>* output)
    {
      output->allocT<CustomGPUProgram>();
    }

    void CustomGPUManager::newBuffer(EDK3::ref_ptr<EDK3::dev::Buffer>* output)
    {
      output->allocT<CustomGPUBuffer>();
    }

    void CustomGPUManager::newTexture1D(const Texture::Format internal_format, const unsigned size, EDK3::ref_ptr<Texture>* output)
    {
      output->allocT<CustomGPUTexture>()->init(Texture::T_1D, internal_format, size, 0, 0);
    }

    void CustomGPUManager::newTexture2D(const Texture::Format internal_format, const unsigned width, const unsigned height, EDK3::ref_ptr<Texture>* output)
    {
      output->allocT<CustomGPUTexture>()->init(Texture::T_2D, internal_format, width, height, 0);
    }

    void CustomGPUManager::newTexture3D(const Texture::Format internal_format, const unsigned width, const unsigned height, const unsigned depth, EDK3::ref_ptr<Texture>* output)
    {
      output->allocT<CustomGPUTexture>()->init(Texture::T_3D, internal_format, width, height, depth);
    }


    
/*
    void CustomGPUManager::enableBlend(BlendParam source, BlendParam destination, BlendOp operation, const float ConstantColor[4])
    {
      GPUManager::enableBlend(source, destination, operation, ConstantColor);
      unsigned int src = 0;
      switch (source)
      {
      case kBlendParam_Zero:
        src = GL_ZERO;
        break;
      case kBlendParam_One:
        src = GL_ONE;
        break;
      case kBlendParam_SourceColor:
        src = GL_SRC_COLOR;
        break;
      case kBlendParam_OneMinusSourceColor:
        src = GL_ONE_MINUS_SRC_COLOR;
        break;
      case kBlendParam_DestinationColor:
        src = GL_DST_COLOR;
        break;
      case kBlendParam_OneMinusDestinationColor:
        src = GL_ONE_MINUS_DST_COLOR;
        break;
      case kBlendParam_SourceAlpha:
        src = GL_SRC_ALPHA;
        break;
      case kBlendParam_OneMinusSourceAlpha:
        src = GL_ONE_MINUS_SRC_ALPHA;
        break;
      case kBlendParam_DestinationAlpha:
        src = GL_DST_ALPHA;
        break;
      case kBlendParam_OneMinusDestinationAlpha:
        src = GL_ONE_MINUS_DST_ALPHA;
        break;
      case kBlendParam_ConstantColor:
        src = GL_CONSTANT_COLOR;
        break;
      case kBlendParam_OneMinusConstantColor:
        src = GL_ONE_MINUS_CONSTANT_COLOR;
        break;
      case kBlendParam_ConstantAlpha:
        src = GL_CONSTANT_ALPHA;
        break;
      case kBlendParam_OneMinusConstantAlpha:
        src = GL_ONE_MINUS_CONSTANT_ALPHA;
        break;
      case kBlendParam_SourceAlphaSaturate:
        src = GL_SRC_ALPHA_SATURATE;
        break;
      }

      unsigned int dst = 0;
      switch (destination)
      {
      case kBlendParam_Zero:
        dst = GL_ZERO;
        break;
      case kBlendParam_One:
        dst = GL_ONE;
        break;
      case kBlendParam_SourceColor:
        dst = GL_SRC_COLOR;
        break;
      case kBlendParam_OneMinusSourceColor:
        dst = GL_ONE_MINUS_SRC_COLOR;
        break;
      case kBlendParam_DestinationColor:
        dst = GL_DST_COLOR;
        break;
      case kBlendParam_OneMinusDestinationColor:
        dst = GL_ONE_MINUS_DST_COLOR;
        break;
      case kBlendParam_SourceAlpha:
        dst = GL_SRC_ALPHA;
        break;
      case kBlendParam_OneMinusSourceAlpha:
        dst = GL_ONE_MINUS_SRC_ALPHA;
        break;
      case kBlendParam_DestinationAlpha:
        dst = GL_DST_ALPHA;
        break;
      case kBlendParam_OneMinusDestinationAlpha:
        dst = GL_ONE_MINUS_DST_ALPHA;
        break;
      case kBlendParam_ConstantColor:
        dst = GL_CONSTANT_COLOR;
        break;
      case kBlendParam_OneMinusConstantColor:
        dst = GL_ONE_MINUS_CONSTANT_COLOR;
        break;
      case kBlendParam_ConstantAlpha:
        dst = GL_CONSTANT_ALPHA;
        break;
      case kBlendParam_OneMinusConstantAlpha:
        dst = GL_ONE_MINUS_CONSTANT_ALPHA;
        break;
      case kBlendParam_SourceAlphaSaturate:
        dst = GL_SRC_ALPHA_SATURATE;
        break;
      }

      unsigned int opp = 0;
      switch (operation)
      {
      case BlendOp::kBlendOp_Add:
        opp = GL_FUNC_ADD;
        break;
      case BlendOp::kBlendOp_Max:
        opp = GL_MAX;
        break;
      case BlendOp::kBlendOp_Min:
        opp = GL_MIN;
        break;
      case BlendOp::kBlendOp_Subtract:
        opp = GL_FUNC_SUBTRACT;
        break;
      case BlendOp::kBlendOp_ReverseSubtract:
        opp = GL_FUNC_REVERSE_SUBTRACT;
        break;
      }
      glEnable(GL_BLEND);
      glBlendFunc(src, dst);
      glBlendEquation(opp);
      if (ConstantColor)
      {
        glBlendColor(ConstantColor[0], ConstantColor[1], ConstantColor[2], ConstantColor[3]);
      }
      else
      {
        glBlendColor(1.0f, 1.0f, 1.0f, 1.0f);  
      }
    }

    
    void CustomGPUManager::disableBlend()
    {
      glDisable(GL_BLEND);
    }*/
/*
    void CustomGPUManager::enableVertexAttribute(const EDK3::dev::Buffer* buffer, const unsigned attribute_index, const EDK3::Type type, const bool normalized, const unsigned offset, const unsigned stride)
    {
      unsigned int size = 0;
      unsigned int t = 0;
      switch (type)
      {
      case T_FLOAT_1:
        size = 1;
        t = GL_FLOAT;
        break;
      case T_FLOAT_2:
        size = 2;
        t = GL_FLOAT;
        break;
      case T_FLOAT_3:
        size = 3;
        t = GL_FLOAT;
        break;
      case T_FLOAT_4:
        size = 4;
        t = GL_FLOAT;
        break;
      case T_DOUBLE_1:
        size = 1;
        t = GL_DOUBLE;
        break;
      case T_DOUBLE_2:
        size = 2;
        t = GL_DOUBLE;
        break;
      case T_DOUBLE_3:
        size = 3;
        t = GL_DOUBLE;
        break;
      case T_DOUBLE_4:
        size = 4;
        t = GL_DOUBLE;
        break;
      case T_INT_1:
        size = 1;
        t = GL_INT;
        break;
      case T_INT_2:
        size = 2;
        t = GL_INT;
        break;
      case T_INT_3:
        size = 3;
        t = GL_INT;
        break;
      case T_INT_4:
        size = 4;
        t = GL_INT;
        break;
      case T_UINT_1:
        size = 1;
        t = GL_UNSIGNED_INT;
        break;
      case T_UINT_2:
        size = 2;
        t = GL_UNSIGNED_INT;
        break;
      case T_UINT_3:
        size = 3;
        t = GL_UNSIGNED_INT;
        break;
      case T_UINT_4:
        size = 4;
        t = GL_UNSIGNED_INT;
        break;
      case T_BYTE_1:
        size = 1;
        t = GL_BYTE;
        break;
      case T_BYTE_2:
        size = 2;
        t = GL_BYTE;
        break;
      case T_BYTE_3:
        size = 3;
        t = GL_BYTE;
        break;
      case T_BYTE_4:
        size = 4;
        t = GL_BYTE;
        break;
      case T_UBYTE_1:
        size = 1;
        t = GL_UNSIGNED_BYTE;
        break;
      case T_UBYTE_2:
        size = 2;
        t = GL_UNSIGNED_BYTE;
        break;
      case T_UBYTE_3:
        size = 3;
        t = GL_UNSIGNED_BYTE;
        break;
      case T_UBYTE_4:
        size = 4;
        t = GL_UNSIGNED_BYTE;
        break;
      case T_SHORT_1:
        size = 1,
        t = GL_SHORT;
        break;
      case T_SHORT_2:
        size = 2;
        t = GL_SHORT;
        break;
      case T_SHORT_3:
        size = 3;
        t = GL_SHORT;
        break;
      case T_SHORT_4:
        size = 4;
        t = GL_SHORT;
        break;
      case T_USHORT_1:
        size = 1;
        t = GL_UNSIGNED_SHORT;
        break;
      case T_USHORT_2:
        size = 2;
        t = GL_UNSIGNED_SHORT;
        break;
      case T_USHORT_3:
        size = 3;
        t = GL_UNSIGNED_SHORT;
        break;
      case T_USHORT_4:
        size = 4;
        t = GL_UNSIGNED_SHORT;
        break;
      }
      unsigned int nrmlze = 0;
      if (normalized)
      {
        nrmlze = GL_TRUE;
      }
      else
      {
        nrmlze = GL_FALSE;
      }
      buffer->bind(Buffer::kTarget_Vertex_Data);
      glVertexAttribPointer(attribute_index, size, t, nrmlze, stride, (void*)offset);
      glEnableVertexAttribArray(attribute_index);
    }

    void CustomGPUManager::disableVertexAttribute(const unsigned attrib_index)
    {
      glDisableVertexAttribArray(attrib_index); 
    }
*/
/*
    void CustomGPUManager::enableCullFaces(const FaceType f)
    {
      GPUManager::enableCullFaces(f);
      unsigned int type = 0;
      switch (f)
      {
      case kFace_Back:
        type = GL_BACK;
        break;
      case kFace_Front:
        type = GL_FRONT;
        break;
      case kFace_FrontAndBack:
        type = GL_FRONT_AND_BACK;
        break;
      }
      glEnable(GL_CULL_FACE);
      glCullFace(type);
    }

    void CustomGPUManager::disableCullFaces()
    {
      glDisable(GL_CULL_FACE);
    }

    void CustomGPUManager::enableScissor(int x, int y, unsigned int width, unsigned int height) {
      GPUManager::enableScissor(x, y, width, height);
      glEnable(GL_SCISSOR_TEST);
      glScissor(x, y, width, height);
      assert(glGetError() == GL_NO_ERROR);
    }

    void CustomGPUManager::disableScissor() {
      GPUManager::disableScissor();
      glDisable(GL_SCISSOR_TEST);
    }
    void CustomGPUManager::enableDepthTest(const CompareFunc f) {
      GPUManager::enableDepthTest(f);
      glEnable(GL_DEPTH_TEST);
      switch (f)
      {
      case kCompareFunc_Never: glDepthFunc(GL_NEVER); break;
      case kCompareFunc_Less: glDepthFunc(GL_LESS); break;
      case kCompareFunc_LessOrEqual: glDepthFunc(GL_LEQUAL); break;
      case kCompareFunc_Equal: glDepthFunc(GL_EQUAL); break;
      case kCompareFunc_NotEqual: glDepthFunc(GL_NOTEQUAL); break;
      case kCompareFunc_GreaterOrEqual: glDepthFunc(GL_GEQUAL); break;
      case kCompareFunc_Greater: glDepthFunc(GL_GREATER); break;
      case kCompareFunc_Always: glDepthFunc(GL_ALWAYS); break;
      default: glDepthFunc(GL_LESS); break;
      }
      assert(glGetError() == GL_NO_ERROR);
    }

    void CustomGPUManager::disableDepthTest() {
      GPUManager::disableDepthTest();
      glDisable(GL_DEPTH_TEST);
    }
    
    
    void CustomGPUManager::drawElements(const DrawMode mode, unsigned count, const EDK3::dev::Buffer* buffer, const EDK3::Type element_type, const unsigned offset) const
    {
      unsigned int m = 0;
      switch (mode)
      {
      case DrawMode::kDrawMode_Lines:
        m = GL_LINES;
        break;
      case DrawMode::kDrawMode_Points:
        m = GL_POINTS;
        break;
      case DrawMode::kDrawMode_Triangles:
        m = GL_TRIANGLES;
        break;
      case DrawMode::kDrawMode_LineLoop:
        m = GL_LINE_LOOP;
        break;
      case DrawMode::kDrawMode_LineStrip:
        m = GL_LINE_STRIP;
        break;
      case DrawMode::kDrawMode_TriangleStrip:
        m = GL_TRIANGLE_STRIP;
        break;
      }

      unsigned int type = 0;
      switch (element_type)
      {
      case Type::T_INT:
        type = GL_INT;
        break;
      case Type::T_BYTE:
        type = GL_BYTE;
        break;
      case Type::T_UINT:
        type = GL_UNSIGNED_INT;
        break;
      case Type::T_SHORT:
        type = GL_SHORT;
        break;
      case Type::T_USHORT:
        type = GL_UNSIGNED_SHORT;
        break;
      case Type::T_UBYTE:
        type = GL_UNSIGNED_BYTE;
        break;
      }
      
      buffer->bind(Buffer::kTarget_Elements);
      glDrawElements(m, count, type, (void*)offset);
    }
*/
    
  }
  
}
