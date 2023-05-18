
#include "EDK3/dev/glew.h"
#include "dev/custom_gpu_shader.h"
#include "EDK3/dev/gpumanager.h"

namespace EDK3
{
  
  namespace dev
  {

    CustomGPUShader::CustomGPUShader() : id_(0) {}

    void CustomGPUShader::loadSource(const Type shader_type, const char* source, const unsigned source_size)
    {
      switch (shader_type)
      {
      case Type::kType_Vertex:
        id_ = glCreateShader(GL_VERTEX_SHADER);
        break;
      case Type::kType_Fragment:
        id_ = glCreateShader(GL_FRAGMENT_SHADER);
        break;
      case Type::kType_Geometry:
        id_ = glCreateShader(GL_GEOMETRY_SHADER);
        break;
      default:
        return;
      }

      glShaderSource(id_, 1, &source, (const GLint*)&source_size);
      EDK3::dev::GPUManager::CheckGLError("Prepare END");
    }

    bool CustomGPUShader::compile(EDK3::scoped_array<char>* output_log)
    {
      int compiled = 0;
      glCompileShader(id_);
      glGetShaderiv(id_, GL_COMPILE_STATUS, &compiled);
      if (output_log != NULL)
      {
        int length = 0;
        //glGetShaderInfoLog(id_, 1024, &length, NULL);
        output_log->alloc(1024);
        glGetShaderInfoLog(id_, 1024, NULL, output_log->get());
      }
      EDK3::dev::GPUManager::CheckGLError("Prepare END");
      return compiled;
    }

    bool CustomGPUShader::is_compiled() const
    {
      int compiled = 0;
      glGetShaderiv(id_, GL_COMPILE_STATUS, &compiled);
      EDK3::dev::GPUManager::CheckGLError("Prepare END");
      return compiled == 1;
    }

    const EDK3::dev::Shader::Type CustomGPUShader::type() const
    {
      int shader_type = 0;
      glGetShaderiv(id_, GL_SHADER_TYPE, &shader_type);

      EDK3::dev::GPUManager::CheckGLError("Prepare END");
      switch (shader_type)
      {
      case GL_VERTEX_SHADER:
        return Type::kType_Vertex;
      case GL_FRAGMENT_SHADER:
        return Type::kType_Fragment;
      case GL_GEOMETRY_SHADER:
        return Type::kType_Geometry;
      default:
        return Type::kType_Invalid;
      }
    }

    unsigned CustomGPUShader::internal_id() const
    {
      return id_;
    }

    CustomGPUShader::~CustomGPUShader()
    {
      if (id_ != 0)
      {
        glDeleteShader(id_); 
      }
    }

    CustomGPUShader& CustomGPUShader::operator=(const CustomGPUShader&)
    {
      return  *this;
    }

    CustomGPUShader::CustomGPUShader(const CustomGPUShader&) {}


    
  }
  
}
