/**
 *
 * @brief Basic material source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#include "material_custom.h"
#include "Lights.h"
#include "EDK3/scoped_ptr.h"
#include "ESAT/time.h"
#include "EDK3/dev/gpumanager.h"

namespace EDK3 {


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
  
//Constructors, destructor and operator= here!!
MaterialCustom::MaterialCustom(){}

MaterialCustom::MaterialCustom(const MaterialCustom&){}

MaterialCustom::MaterialCustom(MaterialCustom&&){}
  
MaterialCustom& MaterialCustom::operator=(const MaterialCustom&)
{
  return *this;
}
  
MaterialCustom::~MaterialCustom()
{
  
}
  
void MaterialCustom::init(const char* vertex_path, const char* fragment_path) {
  //1: Request at least two shaders and one program to the GPU Manager.
  //2: Load the source code to the requested shaders.
  //3: Compile both shaders.
  //4: Attach shaders to the program.
  //5: Finally... link the program!

  EDK3::scoped_array<char> source;
  EDK3::scoped_array<char> error;
  

  
  EDK3::ref_ptr<EDK3::dev::Shader> vertex_shader;
  EDK3::ref_ptr<EDK3::dev::Shader> fragment_shader;

  EDK3::dev::GPUManager::Instance()->newShader(&vertex_shader);
  EDK3::dev::GPUManager::Instance()->newShader(&fragment_shader);
  EDK3::dev::GPUManager::Instance()->newProgram(&program_);
  
  if (!LoadSourceFromFile(fragment_path, source, &error))
  {
    printf("Error: %s", error.get());
  }
  else
  {
    fragment_shader->loadSource(EDK3::dev::Shader::kType_Fragment, source.get(), source.size());
  }
  
  if (!LoadSourceFromFile(vertex_path, source, &error))
  {
    printf("Error: %s", error.get());
  }
  else
  {
    vertex_shader->loadSource(EDK3::dev::Shader::kType_Vertex, source.get(), source.size());
  }

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

bool MaterialCustom::enable(const EDK3::MaterialSettings *mat) const {
  //Enable the material...
  //... and use the uniforms located in the material settings!
  program_->use();
  const MaterialCustomSettings *ms = dynamic_cast<const MaterialCustomSettings*>(mat);
  if (ms)
  {
    int uniform_att;
    uniform_att = program_->get_uniform_position("u_time");
    float time = (float)ESAT::Time();
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT_1, &time);

    uniform_att = program_->get_uniform_position("u_color");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT_4, ms->color());

    uniform_att = program_->get_uniform_position("u_camera_position");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT_3, ms->get_cam_pos());
    
    // Dir Light
    EDK3::ref_ptr<DirLight> light = ms->dir_light();
    
    uniform_att = program_->get_uniform_position("u_dirLight.active");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT, &light->active);
  
    uniform_att = program_->get_uniform_position("u_dirLight.dir");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT_3, light->dir);
  
    uniform_att = program_->get_uniform_position("u_dirLight.diffuse_color");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT_3, light->diffuse_color);

    uniform_att = program_->get_uniform_position("u_dirLight.specular_color");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT_3, light->specular_color);
  
    uniform_att = program_->get_uniform_position("u_dirLight.specular_strength");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT, &light->specular_strength);

    uniform_att = program_->get_uniform_position("u_dirLight.specular_shininess");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT, &light->specular_shininess);


    // Point Light
    EDK3::ref_ptr<PointLight> point = ms->point_light();
    uniform_att = program_->get_uniform_position("u_pointLight.active");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT, &point->active);
    
    uniform_att = program_->get_uniform_position("u_pointLight.pos");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT_3, point->pos);

    //const float *prueba = point->diffuse_color;
    uniform_att = program_->get_uniform_position("u_pointLight.diffuse_color");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT_3, point->diffuse_color);

    uniform_att = program_->get_uniform_position("u_pointLight.specular_color");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT_3, point->specular_color);
  
    uniform_att = program_->get_uniform_position("u_pointLight.specular_strength");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT, &point->specular_strength);

    uniform_att = program_->get_uniform_position("u_pointLight.specular_shininess");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT, &point->specular_shininess);
    
    uniform_att = program_->get_uniform_position("u_pointLight.constant_att");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT, &point->constant_att);
    
    uniform_att = program_->get_uniform_position("u_pointLight.linear_att");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT, &point->linear_att);
    
    uniform_att = program_->get_uniform_position("u_pointLight.quadratic_att");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT, &point->quadratic_att);


    uniform_att = program_->get_uniform_position("u_resolution_x");
    float x = ms->getResolutionX();
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT, &x);
    
    uniform_att = program_->get_uniform_position("u_resolution_y");
    float y = ms->getResolutionY();
    program_->set_uniform_value(uniform_att, EDK3::Type::T_FLOAT, &y);
    

    int texture_pos = 0;
    ms->get_diffuse_texture()->bind(texture_pos);
    uniform_att = program_->get_uniform_position("u_diffuse_color");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_INT_1, &texture_pos);

    texture_pos = 1;
    ms->get_specular_texture()->bind(texture_pos);
    uniform_att = program_->get_uniform_position("u_specular_color");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_INT_1, &texture_pos);



    return true;
  }
  
  return false;
}

void MaterialCustom::setupCamera(const float projection[16],
                                const float view[16]) const {
  int attrib_tag = program_->get_uniform_position("u_projection_matrix");
  program_->set_uniform_value(attrib_tag, T_MAT_4x4, projection);
  attrib_tag = program_->get_uniform_position("u_view_matrix");
  program_->set_uniform_value(attrib_tag, T_MAT_4x4, view);
}

void MaterialCustom::setupModel(const float model[16]) const {
  const int attrib_tag = program_->get_uniform_position("u_model_matrix");
  program_->set_uniform_value(attrib_tag, T_MAT_4x4, model);
}

unsigned int MaterialCustom::num_attributes_required() const {
  //Depending on how attributes the geometry has.
  return 3;
}

EDK3::Attribute MaterialCustom::attribute_at_index(const unsigned int attrib_idx) const {
  //Search on "EDK3::Attribute" enum.
  //Depending on how attributes are stored in the geometry buffer.
  switch (attrib_idx)
  {
    case 0: return EDK3::Attribute::A_POSITION; break;
    case 1: return EDK3::Attribute::A_NORMAL; break;
    case 2: return EDK3::Attribute::A_UV; break;
    default: return EDK3::Attribute::A_NONE;
  }
}

EDK3::Type MaterialCustom::attribute_type_at_index(const unsigned int attrib_idx) const {
  //Search on "EDK3::Type" enum.
  //Depending on how attributes are stored in the geometry buffer.
  switch (attrib_idx)
  {
    case 0: return EDK3::Type::T_FLOAT_3; break;
    case 1: return EDK3::Type::T_FLOAT_3; break;
    case 2: return EDK3::Type::T_FLOAT_2; break;
    default: return EDK3::Type::T_NONE; break;
  }
}
  
} //EDK3
