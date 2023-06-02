/**
 *
 * @brief Custom GPU Manager header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 * Look for OpenGL functions which name is close similar to these functions...
 * 
 */

#ifndef __CUSTOM_GPU_MANAGER_H__
#define __CUSTOM_GPU_MANAGER_H__ 1

#include <stdio.h>
#include "EDK3/dev/opengl.h"
#include "EDK3/dev/gpumanager.h"

namespace EDK3 {

namespace dev {

/**
 * @class CustomGPUManager
 * @brief Clase que representa un administrador personalizado de la GPU.
 *
 * Esta clase hereda de EDK3::dev::GPUManager y se utiliza para gestionar operaciones de la GPU, como la creación de shaders, programas, búferes y texturas, configuración de pruebas de profundidad, mezcla de colores, desactivación de caras, recorte y atributos de vértices.
 */
class CustomGPUManager : public EDK3::dev::GPUManager {
 public:
  /**
 * @brief Crea un nuevo shader.
 * @param output Puntero al puntero donde se almacenará el shader creado.
 */
  virtual void newShader(EDK3::ref_ptr<EDK3::dev::Shader> *output) override;

  /**
   * @brief Crea un nuevo programa.
   * @param output Puntero al puntero donde se almacenará el programa creado.
   */
  virtual void newProgram(EDK3::ref_ptr<EDK3::dev::Program> *output) override;
 
  /**
 * @brief Crea un nuevo búfer.
 * @param output Puntero al puntero donde se almacenará el búfer creado.
 */
  virtual void newBuffer(EDK3::ref_ptr<EDK3::dev::Buffer> *output) override;
   
    /**
   * @brief Crea una nueva textura 1D.
   * @param internal_format Formato interno de la textura.
   * @param size Tamaño de la textura.
   * @param output Puntero al puntero donde se almacenará la textura creada.
   */
  virtual void newTexture1D(const Texture::Format internal_format, 
                            const unsigned int size,  
                            EDK3::ref_ptr<Texture>* output) override;

  /**
 * @brief Crea una nueva textura 2D.
 * @param internal_format Formato interno de la textura.
 * @param width Ancho de la textura.
 * @param height Altura de la textura.
 * @param output Puntero al puntero donde se almacenará la textura creada.
 */
  virtual void newTexture2D(const Texture::Format internal_format, 
                            const unsigned int width, const unsigned int height, 
                            EDK3::ref_ptr<Texture>* output) override;

    /**
   * @brief Crea una nueva textura 3D.
   * @param internal_format Formato interno de la textura.
   * @param width Ancho de la textura.
   * @param height Altura de la textura.
   * @param depth Profundidad de la textura.
   * @param output Puntero al puntero donde se almacenará la textura creada.
   */
  virtual void newTexture3D(const Texture::Format internal_format, 
                            const unsigned int width, const unsigned int height, 
                            const unsigned int depth, 
                            EDK3::ref_ptr<Texture>* output) override;
   

   /*
  virtual void newFramebuffer(EDK3::ref_ptr<Framebuffer>* output) override;
  virtual void clearFrameBuffer(const float rgba[4],
                                const unsigned int FrameBufferOrMask =
                                kFrameBufferColor | kFrameBufferDepth) override;
   */

  
  /**
 * @brief Habilita la prueba de profundidad con la función de comparación especificada.
 * @param f Función de comparación de la prueba de profundidad.
 */
  virtual void enableDepthTest(const CompareFunc f) override;

    /**
   * @brief Deshabilita la prueba de profundidad.
   */
  virtual void disableDepthTest() override;
   

     /**
   * @brief Habilita la mezcla de colores con los parámetros especificados.
   * @param source Parámetro de origen de la mezcla.
   * @param destination Parámetro de destino de la mezcla.
   * @param operation Operación de mezcla.
   * @param ConstantColor Color constante para la mezcla.
   */
  virtual void enableBlend(BlendParam source, 
                           BlendParam destination, 
                           BlendOp operation, 
                           const float ConstantColor[4]) override;

    /**
   * @brief Deshabilita la mezcla de colores.
   */
  void disableBlend();
   

     /**
   * @brief Habilita el desactivado de caras con el tipo de cara especificado.
   * @param f Tipo de cara a desactivar.
   */
  virtual void enableCullFaces(const FaceType f) override;

    /**
   * @brief Deshabilita el desactivado de caras.
   */
  virtual void disableCullFaces() override;
   

    /**
   * @brief Habilita el recorte de área con los parámetros especificados.
   * @param x Coordenada X de la esquina inferior izquierda del área de recorte.
   * @param y Coordenada Y de la esquina inferior izquierda del área de recorte.
   * @param width Ancho del área de recorte.
   * @param height Altura del área de recorte.
   */
  virtual void enableScissor(int x, int y,
                             unsigned int width,
                             unsigned int height) override;

    /**
   * @brief Deshabilita el recorte de área.
   */
  virtual void disableScissor() override;
   

    /**
   * @brief Habilita el atributo de vértice con los parámetros especificados.
   * @param buffer Búfer de vértice asociado al atributo.
   * @param attribute_index Índice del atributo de vértice.
   * @param type Tipo de datos del atributo.
   * @param normalized Especifica si los valores deben normalizarse.
   * @param offset Desplazamiento dentro del búfer de vértice.
   * @param stride Tamaño de la estructura del atributo en el búfer de vértice.
   */
  virtual void enableVertexAttribute(const EDK3::dev::Buffer *buffer,
                                     const unsigned int attribute_index,
                                     const EDK3::Type type,
                                     const bool normalized = false,
                                     const unsigned int offset = 0,
                                     const unsigned int stride = 0) override;
   

    /**
   * @brief Deshabilita el atributo de vértice con el índice especificado.
   * @param attrib_index Índice del atributo de vértice a deshabilitar.
   */
  virtual void disableVertexAttribute(const unsigned int attrib_index) override;
   

     /**
   * @brief Dibuja elementos utilizando el búfer de índices y los parámetros especificados.
   * @param mode Modo de dibujo.
   * @param count Número de elementos a dibujar.
   * @param buffer Búfer de índices.
   * @param element_type Tipo de datos de los elementos en el búfer de índices.
   * @param offset Desplazamiento dentro del búfer de índices.
   */
  virtual void drawElements(const DrawMode mode,
                            unsigned int count,
                            const EDK3::dev::Buffer *buffer,
                            const EDK3::Type element_type = EDK3::Type::T_USHORT,
                            const unsigned int offset = 0) const override;
   

  
  /**
   * @brief Establece si se debe representar el modelo en modo de alambre o no.
   * @param wireframe Valor booleano que indica si se debe representar el modelo en modo de alambre.
   */
  void set_wireframe(bool wireframe);
private:
  bool wireframe_;
}; //CustomGPUManager

} //dev

} //EDK3

#endif //__CUSTOM_GPU_MANAGER__
