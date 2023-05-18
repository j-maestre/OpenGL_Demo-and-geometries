#include "cubemap_material.h"
#include "EDK3/dev/gpumanager.h"
#include "ESAT/time.h"
#include "EDK3/dev/glew.h"

static const char *kLoadFilesErrors[] = {"Can't open the file\0", "Not enough memory\0", "The data si not been loaded correctly\0"};
  
static bool LoadSourceFromFile(const char *file_path, EDK3::scoped_array<char>& source, EDK3::scoped_array<char>* error = nullptr)
{

  if (error != nullptr)
    if (error->valid())
      error->release();

  if (source.valid())
    source.release();
  
  FILE *file = fopen(file_path, "rb");
  if (file == NULL)
  {
    if (error != nullptr)
    {
      error->alloc(strlen(kLoadFilesErrors[0]) + 1);
      error->memSet(0);
      memcpy(error->get(), kLoadFilesErrors[0], error->size());
    }
    return false;
  }

  fseek(file, 0, SEEK_END);
  const unsigned int file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  source.alloc(file_size + 1);
  if (source.valid())
  {
    source[file_size] = '\0';
    const unsigned int elements_loaded = fread(source.get(), 1, file_size, file);
    fclose(file);
    if (elements_loaded != file_size)
    {
      source.release();
      if (error != nullptr)
      {
        error->alloc(strlen(kLoadFilesErrors[2]) + 1);
        error->memSet(0);
        memcpy(error->get(), kLoadFilesErrors[2], error->size());
      }
      return false;
    }
  }
  else
  {
    if (error != nullptr)
    {
      error->alloc(strlen(kLoadFilesErrors[1]) + 1);
      error->memSet(0);
      memcpy(error->get(), kLoadFilesErrors[1], error->size());
    }
    return false;
  }
  return true;
}

namespace EDK3
{
  MaterialCubeMap::MaterialCubeMap()
  {
    
  }

  MaterialCubeMap::~MaterialCubeMap()
  {
    
  }

  void MaterialCubeMap::init(const char* vertex_path, const char* fragment_path)
  {
    EDK3::scoped_array<char> source;
    EDK3::scoped_array<char> error;
  

  
    EDK3::ref_ptr<EDK3::dev::Shader> vertex_shader;
    EDK3::ref_ptr<EDK3::dev::Shader> fragment_shader;
    
    EDK3::dev::GPUManager::Instance()->newShader(&fragment_shader);
    EDK3::dev::GPUManager::Instance()->newShader(&vertex_shader);
    EDK3::dev::GPUManager::Instance()->newProgram(&program_);
  
    
    if (!LoadSourceFromFile(fragment_path, source, &error))
      printf("Error: %s", error.get());
    else
      fragment_shader->loadSource(EDK3::dev::Shader::kType_Fragment, source.get(), source.size());
  
    if (!LoadSourceFromFile(vertex_path, source, &error))
      printf("Error: %s", error.get());
    else
      vertex_shader->loadSource(EDK3::dev::Shader::kType_Vertex, source.get(), source.size());

    
    bool done = false;
  
    done = vertex_shader->compile(&error);
    if (!done)
    {
      printf("Error in compilation of the vertex shader\n");
      printf("%s\n", error.get());
    }
    done = fragment_shader->compile(&error);
    if (!done)
    {
      printf("Error in compilation of the fragment shader\n");
      printf("%s\n", error.get());
    }
    
    program_->attach(vertex_shader.get());
    program_->attach(fragment_shader.get());
  
    done = program_->link(&error);
    if (!done)
    {
      printf("Error in link of the program\n");
      printf("%s\n", error.get());
    }
    
  }

  bool MaterialCubeMap::enable(const MaterialSettings* mat) const
  {
    dev::GPUManager *gpu = dev::GPUManager::Instance();
    gpu->changeDepthMask(false);
    gpu->enableDepthTest(dev::GPUManager::kCompareFunc_LessOrEqual);
    program_->use();
    const Settings *ms = dynamic_cast<const Settings*>(mat);
    if (ms)
    {
      int uniform_att;
      uniform_att = program_->get_uniform_position("u_time");
      float time = (float)ESAT::Time();
      program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT_1, &time);

      ref_ptr<CustomGPUCubeMap> cm = ms->get_cube_map();

      if (cm.valid())
      {
        int texture_pos = 0;
        cm->bind(texture_pos);
        uniform_att = program_->get_uniform_position("u_cube_map_texture");
        program_->set_uniform_value(uniform_att, T_INT_1, &texture_pos);
      }
      
      return true;
    }
    return false;
  }

  void MaterialCubeMap::setupCamera(const float projecton[16], const float view[16]) const
  {
    int attrib_tag = program_->get_uniform_position("u_projection_matrix");
    program_->set_uniform_value(attrib_tag, T_MAT_4x4, projecton);
    attrib_tag = program_->get_uniform_position("u_view_matrix");
    program_->set_uniform_value(attrib_tag, T_MAT_4x4, view);
  }

  void MaterialCubeMap::setupModel(const float model[16]) const
  {
    const int attrib_tag = program_->get_uniform_position("u_model_matrix");
    program_->set_uniform_value(attrib_tag, T_MAT_4x4, model);
  }

  unsigned MaterialCubeMap::num_attributes_required() const
  {
    return 3;
  }

  Attribute MaterialCubeMap::attribute_at_index(const unsigned attrib_idx) const
  {
    switch (attrib_idx)
    {
    case 0: return EDK3::Attribute::A_POSITION; break;
    case 1: return EDK3::Attribute::A_NORMAL; break;
    case 2: return EDK3::Attribute::A_UV; break;
    default: return EDK3::Attribute::A_NONE;
    }
  }

  Type MaterialCubeMap::attribute_type_at_index(const unsigned attrib_index) const
  {
    switch (attrib_index)
    {
    case 0: return EDK3::Type::T_FLOAT_3; break;
    case 1: return EDK3::Type::T_FLOAT_3; break;
    case 2: return EDK3::Type::T_FLOAT_2; break;
    default: return EDK3::Type::T_NONE; break;
    }
  }


  
}
