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
  class MaterialCubeMap : public Material
  {
  public:
    MaterialCubeMap();
    void init(const char* vertex_path, const char* fragment_path);

    virtual bool enable(const MaterialSettings* mat) const override;
    virtual void setupCamera(const float projecton[16], const float view[16]) const override;
    virtual void setupModel(const float model[16]) const override;

    virtual unsigned num_attributes_required() const override;
    virtual Attribute attribute_at_index(const unsigned attrib_idx) const override;
    virtual Type attribute_type_at_index(const unsigned attrib_index) const override;

    class Settings : public MaterialSettings
    {
    public:
      Settings(){}

      void set_cube_map(ref_ptr<CustomGPUCubeMap> texture) {cube_map_texture_ = texture;}

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