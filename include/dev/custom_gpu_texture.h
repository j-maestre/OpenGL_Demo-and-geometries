/**
 *
 * @brief Custom GPU texture header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 * Check the following OpenGL functions:
 *   glActiveTexture
 *   glBindTexture
 *   glGenerateMipmap
 *   glBindTexture
 *   glPixelStorei(GL_UNPACK_ALIGNMENT, GL_UNPACK_LSB_FIRST)
 *   glGenTextures
 *   glDeleteTextures
 *   glTexImage(1D, 2D, 3D)
 *   glTexParameteri(GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, 
 *                   GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_R, 
 *                   GL_TEXTURE_WRAP_S)
 *
 */

#ifndef __CUSTOM_GPU_TEXTURE_H__
#define __CUSTOM_GPU_TEXTURE_H__ 1

#include "EDK3/ref_ptr.h"
#include "EDK3/texture.h"

typedef unsigned int GLuint;

namespace EDK3 {

/**
 * @class CustomGPUTexture
 * @brief Clase que representa una textura de GPU personalizada.
 *
 * Esta clase hereda de EDK3::Texture y proporciona funcionalidades adicionales para personalizar la textura de GPU.
 */
class CustomGPUTexture : public EDK3::Texture {
 public:
  /**
   * @brief Constructor de la clase CustomGPUTexture.
   */
  CustomGPUTexture();

  /**
   * @brief Inicializa la textura con los parámetros especificados.
   *
   * @param t Tipo de textura.
   * @param internal_format Formato interno de la textura.
   * @param width Ancho de la textura.
   * @param height Altura de la textura.
   * @param depth Profundidad de la textura.
   */
  void init(Type t, Format internal_format, unsigned int width,
            unsigned int height, unsigned int depth);

    /**
   * @brief Establece los datos de la textura.
   *
   * @param f Formato de los datos.
   * @param t Tipo de los datos.
   * @param data Puntero a los datos.
   * @param mipmap_LOD Nivel de detalle de la textura para los mapas mip.
   */
  virtual void set_data(const Format f, 
                        const EDK3::Type t, 
                        const void* data, 
                        unsigned int mipmap_LOD = 0) override;

  /**
   * @brief Enlaza la textura a la unidad de textura especificada.
   *
   * @param textUnit Unidad de textura a la que se va a enlazar la textura.
   */
  virtual void bind(unsigned int textUnit) const override;

  /**
   * @brief Obtiene el ID interno de la textura.
   *
   * @return El ID interno de la textura.
   */
  virtual unsigned int internal_id() const override;

  /**
   * @brief Establece el filtro de minimización de la textura.
   *
   * @param f Filtro de minimización.
   */
  virtual void set_min_filter(Filter f) override;

  /**
   * @brief Establece el filtro de magnificación de la textura.
   *
   * @param f Filtro de magnificación.
   */
  virtual void set_mag_filter(Filter f) override;


  /**
   * @brief Establece el modo de envoltura S de la textura.
   *
   * @param c Modo de envoltura S.
   */
  virtual void set_wrap_s(Wrap c) override;

  /**
   * @brief Establece el modo de envoltura T de la textura.
   *
   * @param c Modo de envoltura T.
   */
  virtual void set_wrap_t(Wrap c) override;

  /**
 * @brief Establece el modo de envoltura R de la textura.
 *
 * @param c Modo de envoltura R.
 */
  virtual void set_wrap_r(Wrap c) override;

  /**
   * @brief Genera los mapas mip de la textura.
   */
  virtual void generateMipmaps() const override;

 protected:
  virtual ~CustomGPUTexture();

  //TODO any data here?
  unsigned int id_;
  unsigned int type_;
  unsigned int internal_format_;
  unsigned int width_;
  unsigned int height_;
  unsigned int depth_;
 
 private:
  CustomGPUTexture(const CustomGPUTexture&);
  CustomGPUTexture& operator=(const CustomGPUTexture&);

}; //CustomGPUTexture

} //EDK3

#endif //__CUSTOM_GPU_TEXTURE_H__
