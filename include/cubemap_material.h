#ifndef __CUBE_MAP_MATERIAL_H__
#define __CUBE_MAP_MATERIAL_H__ 1

#include "custom_gpu_cubemap.h"
#include "EDK3/ref_ptr.h"
#include "EDK3/material.h"
#include "EDK3/materialsettings.h"
#include "EDK3/dev/program.h"
#include "EDK3/dev/shader.h"
#include "EDK3/texture.h"

namespace EDK3
{

/**
 * @class MaterialCubeMap
 * @brief Represents a cube map material derived from Material.
 *
 * This class defines a cube map material used for rendering.
 */
  class MaterialCubeMap : public Material
  {
  public:
    /**
    * @brief Default constructor.
    */
    MaterialCubeMap();
    /**
    * @brief Initializes the cube map material.
    *
    * @param vertex_path The vertex shader file path.
    * @param fragment_path The fragment shader file path.
    */
    void init(const char* vertex_path, const char* fragment_path);

    /**
    * @brief Enables the cube map material with the specified settings.
    *
    * @param mat The material settings.
    * @return True if the material is enabled successfully, false otherwise.
    */
    virtual bool enable(const MaterialSettings* mat) const override;

    /**
    * @brief Sets up the camera for rendering.
    *
    * @param projection The projection matrix.
    * @param view The view matrix.
    */
    virtual void setupCamera(const float projecton[16], const float view[16]) const override;

    /**
    * @brief Sets up the model for rendering.
    *
    * @param model The model matrix.
    */
    virtual void setupModel(const float model[16]) const override;

    /**
    * @brief Returns the number of attributes required by the material.
    *
    * @return The number of required attributes.
    */
    virtual unsigned num_attributes_required() const override;

    /**
    * @brief Returns the attribute at the specified index.
    *
    * @param attrib_idx The attribute index.
    * @return The attribute at the specified index.
    */
    virtual Attribute attribute_at_index(const unsigned attrib_idx) const override;

      /**
      * @brief Returns the type of the attribute at the specified index.
      *
      * @param attrib_index The attribute index.
      * @return The type of the attribute at the specified index.
      */
    virtual Type attribute_type_at_index(const unsigned attrib_index) const override;


    /**
    * @class Settings
    * @brief Represents the settings for the MaterialCubeMap.
    *
    * This class provides settings specific to the MaterialCubeMap.
    */
    class Settings : public MaterialSettings
    {
    public:
      /**
      * @brief Default constructor.
      */
      Settings(){}

      /**
      * @brief Sets the cube map texture for the material.
      *
      * @param texture The cube map texture.
      */
      void set_cube_map(ref_ptr<CustomGPUCubeMap> texture) {cube_map_texture_ = texture;}

      /**
      * @brief Returns the cube map texture of the material.
      *
      * @return The cube map texture.
      */
      ref_ptr<CustomGPUCubeMap> get_cube_map() const {return cube_map_texture_;}
    protected:
      virtual ~Settings(){}

    private:
      ref_ptr<CustomGPUCubeMap> cube_map_texture_;
    };

  protected:
    virtual ~MaterialCubeMap();

  private:
    ref_ptr<dev::Program> program_;

    MaterialCubeMap(const MaterialCubeMap&) = delete;
    MaterialCubeMap(MaterialCubeMap&&) = delete;
    MaterialCubeMap& operator=(const MaterialCubeMap&) = delete;
  };
} //EDK3

#endif //__CUBE_MAP_MATERIAL_H__