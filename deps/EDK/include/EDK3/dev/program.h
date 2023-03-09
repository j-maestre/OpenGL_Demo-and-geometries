#ifndef INCLUDE_EDK3_DEV_PROGRAM_H_
#define INCLUDE_EDK3_DEV_PROGRAM_H_ 1

#include <EDK3/referenced.h>
#include <EDK3/scoped_array.h>
#include <EDK3/constants.h>

namespace EDK3 {
namespace dev {

  class Shader;
  class Uniform;
  /* OpenGL Calls:
  glAttachShader
  glDeleteProgram
  glLinkProgram
  glUseProgram
  glGetUniformLocation
  glCreateProgram  
  glGetProgramiv
  glGetProgramInfoLog
  glGetAttribLocation
  glUniform(1f,2f,Matrix4f,...)
  glBindAttribLocation // optional
  */
  class Program : public virtual Referenced {
  public:
    virtual void attach(Shader *) = 0;
    virtual bool link(scoped_array<char> *link_log = 0L) = 0; 
    virtual void use() const = 0; 
    virtual  int get_attrib_location(const char *name) const = 0;
    virtual int  get_uniform_position(const char *name) const = 0;
    virtual void set_uniform_value(
        const int uniform_pos,
        const Type uniform_type,
        const float *) const = 0;
    virtual void set_uniform_value(
        const int uniform_pos,
        const Type uniform_type,
        const int*) const = 0;
    virtual void set_uniform_value(
        const int uniform_pos,
        const Type uniform_type,
        const unsigned int*) const = 0;

    /** returns the internal program ID*/
    virtual unsigned int internal_id() const = 0;
  protected:
    Program() {}
    virtual ~Program() {}

  private:
    Program(const Program&);
    Program& operator=(const Program&);
  };

}} /* end of EDK3::dev Namespace */

#endif
