/**
 *
 * @brief Custom GPU program header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 * Check the following OpenGL functions:
 *   glAttachShader
 *   glDeleteProgram
 *   glLinkProgram
 *   glUseProgram
 *   glGetUniformLocation
 *   glCreateProgram  
 *   glGetProgramiv
 *   glGetProgramInfoLog
 *   glGetAttribLocation
 *   glUniform(1f, 2f, Matrix2fv...)
 *   glBindAttribLocation // optional
 *
 */

#ifndef __CUSTOM_GPU_PROGRAM_H__
#define __CUSTOM_GPU_PROGRAM_H__ 1

#include "EDK3/dev/program.h"
#include "EDK3/dev/shader.h"

typedef unsigned int GLuint;

namespace EDK3 {

namespace dev {

class CustomGPUProgram : public EDK3::dev::Program {
 public:
  CustomGPUProgram();

  virtual void attach(EDK3::dev::Shader* shader) override;
  virtual bool link(EDK3::scoped_array<char>* link_log) override;
  virtual void use() const override;
  virtual int get_attrib_location(const char* name) const override;
  virtual int get_uniform_position(const char* name) const override;
  virtual void set_uniform_value(const int uniform_pos,
                                 const EDK3::Type uniform_type,
                                 const float* number) const override;
  virtual void set_uniform_value(const int uniform_pos,
                                 const EDK3::Type uniform_type,
                                 const int* number) const override;
  virtual void set_uniform_value(const int uniform_pos,
                                 const EDK3::Type uniform_type,
                                 const unsigned int* number) const;
  virtual unsigned int internal_id() const override;


 protected:
  virtual ~CustomGPUProgram();

  //TODO any data here?
  unsigned int id_;
  
 private:
  CustomGPUProgram(const CustomGPUProgram&);
  CustomGPUProgram& operator=(const CustomGPUProgram&);

}; //CustomGPUProgram

} //dev

} //EDK3

#endif //__CUSTOM_GPU_PROGRAM_H__
