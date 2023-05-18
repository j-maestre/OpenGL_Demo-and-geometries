/**
 *
 * @brief Custom GPU shader header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 * Check the following OpenGL functions:
 *   glCompileShader
 *   glDeleteShader
 *   glShaderSource
 *   glGetShaderiv
 *   glGetShaderInfoLog
 *   glCreateShader
 *
 */

#ifndef __CUSTOM_GPU_SHADER_H__
#define __CUSTOM_GPU_SHADER_H__ 1

#include "EDK3/dev/shader.h"

typedef unsigned int GLuint;

namespace EDK3 {

namespace dev {

class CustomGPUShader : public EDK3::dev::Shader {
 public:
  CustomGPUShader();

  virtual void loadSource(const Type shader_type, 
                          const char *source,
                          const unsigned int source_size) override;

  virtual bool compile(EDK3::scoped_array<char> *output_log = NULL) override;
  virtual bool is_compiled() const override;
  virtual const EDK3::dev::Shader::Type type() const override;
  virtual unsigned int internal_id() const override;

 protected:
  virtual ~CustomGPUShader();

  //TODO any data here?
  unsigned int id_;
 
 private:
  CustomGPUShader(const CustomGPUShader&);
  CustomGPUShader& operator=(const CustomGPUShader&);

}; //CustomGPUShader

} //dev

} //EDK3

#endif //__CUSTOM_GPU_SHADER_H__
