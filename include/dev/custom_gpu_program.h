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

/**
 * @class CustomGPUProgram
 * @brief Clase que representa un programa de GPU personalizado.
 *
 * Esta clase hereda de EDK3::dev::Program y proporciona funcionalidades adicionales para personalizar el programa de GPU.
 */
class CustomGPUProgram : public EDK3::dev::Program {
 public:
    /**
   * @brief Constructor de la clase CustomGPUProgram.
   */
  CustomGPUProgram();

  /**
   * @brief Adjunta un shader al programa.
   *
   * @param shader Puntero al shader a adjuntar.
   */
  virtual void attach(EDK3::dev::Shader* shader) override;

    /**
   * @brief Enlaza el programa y genera el programa ejecutable en el hardware.
   *
   * @param link_log Puntero a un array que almacenará el registro de enlace del programa.
   * @return Valor booleano que indica si el enlace del programa fue exitoso.
   */
  virtual bool link(EDK3::scoped_array<char>* link_log) override;

  /**
   * @brief Activa el uso del programa en el contexto actual.
   */  
  virtual void use() const override;

    /**
   * @brief Obtiene la ubicación del atributo con el nombre especificado en el programa.
   *
   * @param name Nombre del atributo.
   * @return La ubicación del atributo o -1 si no se encuentra.
   */
  virtual int get_attrib_location(const char* name) const override;

  /**
   * @brief Obtiene la posición del uniform con el nombre especificado en el programa.
   *
   * @param name Nombre del uniform.
   * @return La posición del uniform o -1 si no se encuentra.
   */
  virtual int get_uniform_position(const char* name) const override;

  /**
   * @brief Establece el valor de un uniform de tipo float en el programa.
   *
   * @param uniform_pos Posición del uniform.
   * @param uniform_type Tipo de uniform.
   * @param number Puntero al valor float a establecer.
   */
  virtual void set_uniform_value(const int uniform_pos,
                                 const EDK3::Type uniform_type,
                                 const float* number) const override;

  /**
 * @brief Establece el valor de un uniform de tipo int en el programa.
 *
 * @param uniform_pos Posición del uniform.
 * @param uniform_type Tipo de uniform.
 * @param number Puntero al valor int a establecer.
 */
  virtual void set_uniform_value(const int uniform_pos,
                                 const EDK3::Type uniform_type,
                                 const int* number) const override;

  /**
 * @brief Establece el valor de un uniform de tipo int en el programa.
 *
 * @param uniform_pos Posición del uniform.
 * @param uniform_type Tipo de uniform.
 * @param number Puntero al valor int a establecer.
 */
  virtual void set_uniform_value(const int uniform_pos,
                                 const EDK3::Type uniform_type,
                                 const unsigned int* number) const;

  /**
 * @brief Obtiene el ID interno del programa.
 *
 * @return El ID interno del programa.
 */
  virtual unsigned int internal_id() const override;


 protected:
  /**
 * @brief Destructor virtual de la clase CustomGPUProgram.
 */
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
