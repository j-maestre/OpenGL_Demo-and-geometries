#ifndef INCLUDE_EDK3_DEV_SHADER_H_
#define INCLUDE_EDK3_DEV_SHADER_H_ 1

#include <EDK3/referenced.h>
#include <EDK3/scoped_array.h>

namespace EDK3 {
namespace dev {
  /*OpenGL Calls used:
    glCompileShader
    glDeleteShader
    glShaderSource
    glGetShaderiv
    glGetShaderInfoLog
    glCreateShader
  */
  class Shader : public Referenced {
  public:
    // Type of the shader
    enum Type {
      kType_Invalid,
      kType_Vertex,
      kType_Fragment,
      kType_Geometry,
    };

    // Loads the source of the Shader
    virtual void loadSource(
        const Type shader_type,
        const char *source,
        const unsigned int source_size) = 0;

    // Compiles the shader. Optionally it can fill the output log of the compilation
    // Returns true if the shader was successfully compiled
    virtual bool compile(scoped_array<char> *output_log = NULL) = 0;
    // Checks if the shader is compiled
    virtual bool is_compiled() const = 0;

    // Returns the type of shader
    virtual const Type type() const = 0;

    virtual unsigned int internal_id() const = 0;

  protected:
    Shader() {}
    virtual ~Shader() {}

  private:
    Shader(const Shader&);
    Shader& operator=(const Shader&);
  };

}} /* end of EDK3::dev Namespace */

#endif
