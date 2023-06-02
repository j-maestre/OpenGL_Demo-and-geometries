/**
 *
 * @brief Custom GPU buffer header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 * Check the following OpenGL functions:
 *   glBindBuffer
 *   glBufferData
 *   glBufferSubData
 *   glDeleteBuffers
 *   glGenBuffers
 * 
 */

#ifndef __CUSTOM_GPU_BUFFER_H__
#define __CUSTOM_GPU_BUFFER_H__ 1

#include "EDK3/dev/buffer.h"

typedef unsigned int GLuint;

namespace EDK3 {

namespace dev {

/**
 * @class CustomGPUBuffer
 * @brief Clase que representa un búfer personalizado de la GPU.
 *
 * Esta clase hereda de EDK3::dev::Buffer y se utiliza para gestionar un búfer personalizado en la unidad de procesamiento gráfico (GPU).
 */
class CustomGPUBuffer : public EDK3::dev::Buffer {
 public:
  /**
   * @brief Constructor de CustomGPUBuffer.
   */
  CustomGPUBuffer();

  /**
   * @brief Inicializa el búfer con el tamaño especificado.
   * @param size Tamaño del búfer.
   */
  virtual void init(unsigned int size) override;

  /**
   * @brief Vincula el búfer a un destino específico.
   * @param t Destino al que se vincula el búfer.
   */
  virtual void bind(const Target t) const override;

  /**
   * @brief Devuelve el tamaño del búfer.
   * @return Tamaño del búfer.
   */
  virtual unsigned int size() const override;

  /**
   * @brief Carga los datos en el búfer.
   * @param data Puntero a los datos a cargar.
   * @param size Tamaño de los datos a cargar.
   * @param offset Desplazamiento dentro del búfer donde se cargan los datos (opcional, valor predeterminado: 0).
   */
  virtual void uploadData(const void *data, unsigned int size,
                          unsigned int offset = 0) override;

  /**
   * @brief Libera los recursos asociados al búfer.
   */
  virtual void release() override;


 protected:
   /**
   * @brief Destructor virtual protegido de CustomGPUBuffer.
   */
  virtual ~CustomGPUBuffer();

  //TODO any data here?
  unsigned int size_;
  unsigned int id_;

 private:
  CustomGPUBuffer(const CustomGPUBuffer&);
  CustomGPUBuffer& operator=(const CustomGPUBuffer&);

}; //CustomGPUBuffer

} //dev

} //EDK3

#endif //__CUSTOM_GPU_BUFFER_H__
