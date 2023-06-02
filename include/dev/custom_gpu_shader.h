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

/**
 * @class CustomGPUShader
 * @brief Clase que representa un shader de GPU personalizado.
 *
 * Esta clase hereda de EDK3::dev::Shader y proporciona funcionalidades adicionales para personalizar el shader de GPU.
 */
class CustomGPUShader : public EDK3::dev::Shader {
 public:
  /**
 * @brief Constructor de la clase CustomGPUShader.
 */
  CustomGPUShader();

  /**
   * @brief Carga el código fuente del shader.
   *
   * @param shader_type Tipo de shader.
   * @param source Puntero al código fuente del shader.
   * @param source_size Tamaño del código fuente en bytes.
   */
  virtual void loadSource(const Type shader_type, 
                          const char *source,
                          const unsigned int source_size) override;

  /**
 * @brief Compila el shader.
 *
 * @param output_log Puntero a un array que almacenará el registro de compilación del shader.
 * @return Valor booleano que indica si la compilación del shader fue exitosa.
 */
  virtual bool compile(EDK3::scoped_array<char> *output_log = NULL) override;

  /**
 * @brief Verifica si el shader está compilado.
 *
 * @return Valor booleano que indica si el shader está compilado.
 */
  virtual bool is_compiled() const override;

  /**
   * @brief Obtiene el tipo de shader.
   *
   * @return El tipo de shader.
   */
  virtual const EDK3::dev::Shader::Type type() const override;

  /**
   * @brief Obtiene el ID interno del shader.
   *
   * @return El ID interno del shader.
   */
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
