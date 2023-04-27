/**
 *
 * @brief Basic material source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#include "material_basic.h"

#include "EDK3/scoped_ptr.h"
#include "EDK3/dev/gpumanager.h"


namespace EDK3 {

static const char kExampleVertexShader1[] = {
  "#version 330\n"
  "uniform..."
};
#define GLSL(x) "#version 330\n"#x
static const char* kExampleVertexShader = GLSL(
  uniform mat4 u_model_matrix;
  uniform mat4 u_view_matrix;
  uniform mat4 u_projection_matrix;

  layout(location = 0) in vec3 a_position;
  layout(location = 1) in vec3 a_normal;
  layout(location = 2) in vec2 a_uv;

  out vec3 normal_;
  out vec2 uv_;
  
  void main()
  {
    uv_ = a_uv;
    //normal_ = a_normal;
    normal_ = vec3(u_model_matrix) * a_normal;
    gl_Position = (u_projection_matrix * u_view_matrix * u_model_matrix) * vec4(a_position, 1.0);
  }
);
  
static const char* kExampleFragmentShader = GLSL(
  
  layout(location = 0) out vec4 fragColor;
  in vec3 normal_;
  in vec2 uv_;

  vec3 direction = vec3(1.0, -1.0, 0.0);
  vec3 diffuse = vec3(1.0, 0.5, 0.0);
  void main(){

    //direction.x = cos(u_time * 0.001) + 0.5;
    float impacto = max(dot(normal_, direction), 0.0);
    vec3 diffuse = impacto * diffuse;
    fragColor = vec4(uv_,1.0, 1.0);
    //fragColor = vec4(diffuse, 1.0);
    //fragColor = vec4(normal_, 1.0);
  }
);

static void LogError(const EDK3::scoped_array<char>& error)
{
  printf("%s\n", error.get());
}

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
MaterialBasic::MaterialBasic(){}

MaterialBasic::MaterialBasic(const MaterialBasic&){}

MaterialBasic::MaterialBasic(MaterialBasic&&){}
  
MaterialBasic& MaterialBasic::operator=(const MaterialBasic&)
{
  return *this;
}
  
MaterialBasic::~MaterialBasic()
{
  
}
  
void MaterialBasic::init() {
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

    fragment_shader->loadSource(EDK3::dev::Shader::kType_Fragment, kExampleFragmentShader, strlen(kExampleFragmentShader) + 1);
    
    vertex_shader->loadSource(EDK3::dev::Shader::kType_Vertex, kExampleVertexShader, strlen(kExampleVertexShader) + 1);

  bool done = false;
  
  done = vertex_shader->compile(&error);
  if (!done)
  {
    printf("Error in compilation of the vertex shader\n");
    LogError(error);
  }
  done = fragment_shader->compile(&error);
  if (!done)
  {
    printf("Error in compilation of the fragment shader\n");
    LogError(error);
  }

  program_->attach(vertex_shader.get());
  program_->attach(fragment_shader.get());
  
  done = program_->link(&error);
  if (!done)
  {
    printf("Error in link of the program\n");
    LogError(error);
  }
  
}

bool MaterialBasic::enable(const EDK3::MaterialSettings *mat) const {
  //Enable the material...
  //... and use the uniforms located in the material settings!
  program_->use();
  return true;
}

void MaterialBasic::setupCamera(const float projection[16],
                                const float view[16]) const {
  int attrib_tag = program_->get_uniform_position("u_projection_matrix");
  program_->set_uniform_value(attrib_tag, T_MAT_4x4, projection);
  attrib_tag = program_->get_uniform_position("u_view_matrix");
  program_->set_uniform_value(attrib_tag, T_MAT_4x4, view);
}

void MaterialBasic::setupModel(const float model[16]) const {
  const int attrib_tag = program_->get_uniform_position("u_model_matrix");
  program_->set_uniform_value(attrib_tag, T_MAT_4x4, model);
}

unsigned int MaterialBasic::num_attributes_required() const {
  //Depending on how attributes the geometry has.
  return 3;
}

EDK3::Attribute MaterialBasic::attribute_at_index(const unsigned int attrib_idx) const {
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

EDK3::Type MaterialBasic::attribute_type_at_index(const unsigned int attrib_idx) const {
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
