#include "EDK3/dev/glew.h"
#include "dev/custom_gpu_program.h"

namespace EDK3
{
  
  namespace dev
  {

    CustomGPUProgram::CustomGPUProgram()
    {
      id_ = glCreateProgram();
    }

    CustomGPUProgram::~CustomGPUProgram()
    {
      glDeleteProgram(id_);
    }

    CustomGPUProgram& CustomGPUProgram::operator=(const CustomGPUProgram&)
    {
      return *this;
    }

    CustomGPUProgram::CustomGPUProgram(const CustomGPUProgram&)
    {
      
    }


    
    void CustomGPUProgram::attach(EDK3::dev::Shader* shader)
    {
      glAttachShader(id_, shader->internal_id());
    }

    bool CustomGPUProgram::link(EDK3::scoped_array<char>* link_log)
    {
      int linked = 0;
      glLinkProgram(id_);
      glGetProgramiv(id_, GL_LINK_STATUS, &linked);
      if (link_log != NULL)
      {
        int length = 0;
        //glGetProgramInfoLog(id_, 1024, &length, NULL);
        link_log->alloc(1024);
        glGetProgramInfoLog(id_, 1024, &length, link_log->get());
      }

      return linked;
    }

  int CustomGPUProgram::get_attrib_location(const char* name) const
  {
    return glGetAttribLocation(id_, name);
  }

  int CustomGPUProgram::get_uniform_position(const char* name) const
  {
    return glGetUniformLocation(id_, name);
  }

  unsigned CustomGPUProgram::internal_id() const
  {
    return id_;
  }

  void CustomGPUProgram::use() const
  {
    glUseProgram(id_);
  }

    void EDK3::dev::CustomGPUProgram::set_uniform_value(const int uniform_pos, const EDK3::Type uniform_type, const float* number) const {
      switch (uniform_type)
      {
      case T_FLOAT_1: glUniform1f(uniform_pos, number[0]); break;
      case T_FLOAT_2: glUniform2f(uniform_pos, number[0], number[1]); break;
      case T_FLOAT_3: glUniform3f(uniform_pos, number[0], number[1], number[2]); break;
      case T_FLOAT_4: glUniform4f(uniform_pos, number[0], number[1], number[2], number[3]); break;
      case T_MAT_2x2: glUniformMatrix2fv(uniform_pos, 1, false, number); break;
      case T_MAT_3x3: glUniformMatrix3fv(uniform_pos, 1, false, number); break;
      case T_MAT_4x4: glUniformMatrix4fv(uniform_pos, 1, false, number); break;
      default:
        break;
      }
    }

    void EDK3::dev::CustomGPUProgram::set_uniform_value(const int uniform_pos, const EDK3::Type uniform_type, const int* number) const {
      switch (uniform_type)
      {
      case T_INT_1: glUniform1i(uniform_pos, number[0]); break;
      case T_INT_2: glUniform2i(uniform_pos, number[0], number[1]); break;
      case T_INT_3: glUniform3i(uniform_pos, number[0], number[1], number[2]); break;
      case T_INT_4: glUniform4i(uniform_pos, number[0], number[1], number[2], number[3]); break;
      default:
        break;
      }
    }

    void EDK3::dev::CustomGPUProgram::set_uniform_value(const int uniform_pos, const EDK3::Type uniform_type, const unsigned int* number) const {
      switch (uniform_type)
      {
      case T_UINT_1: glUniform1ui(uniform_pos, number[0]); break;
      case T_UINT_2: glUniform2ui(uniform_pos, number[0], number[1]); break;
      case T_UINT_3: glUniform3ui(uniform_pos, number[0], number[1], number[2]); break;
      case T_UINT_4: glUniform4ui(uniform_pos, number[0], number[1], number[2], number[3]); break;
      default:
        break;
      }
    }






    
  }
  
}
