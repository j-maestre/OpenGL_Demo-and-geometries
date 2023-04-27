/**
 *
 * @brief Basic postprocess material source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#include "postprocess_basic.h"
#include <stdio.h>
#include "ESAT/time.h"
#include "EDK3/dev/gpumanager.h"
#include "ESAT/math.h"


namespace EDK3 {
  
#define GLSL(x) "#version 330\n"#x
static const char kVertexShader[] = GLSL(
  layout(location = 0) in vec3 a_position;\n
  layout(location = 1) in vec3 a_normal;\n
  layout(location = 2) in vec2 a_uv;\n
  \n
  uniform mat4 u_model_matrix;\n
  uniform mat4 u_view_matrix;\n
  uniform mat4 u_projection_matrix;\n
  out vec2 s_uv;\n
  out vec3 s_normal;\n
  \n
    void main(){\n
      gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vec4(a_position, 1.0);\n
      s_uv = a_uv;\n
      s_normal = mat3(u_model_matrix) * a_normal;\n
    }\n
  );

static const char kFragmentShader[] = GLSL(
  layout(location = 0) out vec4 fragColor;\n
  uniform float u_time;\n
  uniform sampler2D u_texture;\n
  uniform vec4 u_color;\n
  in vec2 s_uv;\n
  in vec3 s_normal;\n
  \n
  void main(){\n
    \n
    fragColor = texture(u_texture, s_uv) * u_color;\n
  }\n

);
static const char kFragmentShader_gray_scale[] = GLSL(
  layout(location = 0) out vec4 fragColor;\n
  uniform float u_time;\n
  uniform sampler2D u_texture;\n
  uniform vec4 u_color;\n
  in vec2 s_uv;\n
  in vec3 s_normal;\n
  \n
  void main(){\n
    \n
    vec4 texture_gray = texture(u_texture, s_uv);\n

    float gray = (texture_gray.x + texture_gray.y + texture_gray.z) / 3;\n
    vec4 gray_color = vec4(gray, gray, gray, 1.0);\n

    fragColor = gray_color;\n
  }\n

);
static const char kFragmentShader_sepia[] = GLSL(
  layout(location = 0) out vec4 fragColor;\n
  uniform float u_time;\n
  uniform sampler2D u_texture;\n
  uniform vec4 u_color;\n
  in vec2 s_uv;\n
  in vec3 s_normal;\n
  \n
  void main(){\n
    \n
    vec4 texture_color = texture(u_texture, s_uv);\n

    float outputRed = (texture_color.x * 0.393) + (texture_color.y * 0.769) + (texture_color.z * 0.189);
    float outputGreen = (texture_color.x * 0.349) + (texture_color.y * 0.686) + (texture_color.z * 0.168);
    float outputBlue = (texture_color.x * 0.272) + (texture_color.y * 0.534) + (texture_color.z * 0.131);

    vec4 color = vec4(outputRed, outputGreen, outputBlue, 1.0);\n

    fragColor = color;\n
    //fragColor = texture(u_texture, s_uv);\n
  }\n

);

static const char kFragmentShader_night_vision[] = GLSL(
  layout(location = 0) out vec4 fragColor;\n
  uniform float u_time;\n
  uniform sampler2D u_texture;\n
  uniform vec4 u_color;\n
  in vec2 s_uv;\n
  in vec3 s_normal;\n
  \n
  void main(){\n
    \n
    vec4 texture = texture(u_texture, s_uv);\n

    float color = (texture.x + texture.y + texture.z) / 3;\n
    vec4 output_color = vec4(color, color * 2.0, color, 1.0);\n

    fragColor = output_color;\n
  }\n

);

static const char kFragmentShader_inverted_colors[] = GLSL(
  layout(location = 0) out vec4 fragColor;\n
  uniform float u_time;\n
  uniform sampler2D u_texture;\n
  uniform vec4 u_color;\n
  in vec2 s_uv;\n
  in vec3 s_normal;\n
  \n
  void main(){\n
    \n
    vec4 color = texture(u_texture, s_uv);
    color.x = 1-color.x;
    color.y = 1-color.y;
    color.z = 1-color.z;
    fragColor = color;\n
  }\n

);



static const char kFragmentShader_edge_detection[] = GLSL(
  layout(location = 0) out vec4 fragColor;\n
  uniform float u_time;\n
  uniform sampler2D u_texture;\n
  uniform vec4 u_color;\n
  in vec2 s_uv;\n
  in vec3 s_normal;\n
  ivec2 texture_size = textureSize(u_texture, 0);
  vec2 step_size = 1.0/texture_size;\n
    vec2 offsets[9] = vec2[](\n
        vec2(-step_size.x,  -step_size.y),\n
        vec2( 0.0f,         -step_size.y),\n
        vec2( step_size.x,  -step_size.y),\n
        vec2(-step_size.x,   0.0f),\n
        vec2( 0.0f,          0.0f),\n
        vec2( step_size.x,   0.0f),\n
        vec2(-step_size.x,  +step_size.y),\n
        vec2( 0.0f,         +step_size.y),\n
        vec2( step_size.x,   step_size.y)\n
    );\n

    float kernel[9] = float[](\n
        -1, -1, -1,\n
        -1,  9, -1,\n
        -1, -1, -1\n
    );\n

void main() {
    vec4 sum = vec4(0.0);\n

    for(int i = 0; i < 9; i++) {\n
        sum += texture(u_texture, s_uv + offsets[i]) * kernel[i];\n
    }\n

    sum.a = 1.0;\n
    fragColor = sum;\n
}

);

PostprocessBasic::PostprocessBasic() { }
PostprocessBasic::~PostprocessBasic() { }
PostprocessBasic::PostprocessBasic(const PostprocessBasic& other) {
  program_ = other.program_;
}

PostprocessBasic::PostprocessBasic(PostprocessBasic&& other) {
  program_ = other.program_;
  other.program_.release();
}
PostprocessBasic& PostprocessBasic::operator=(const PostprocessBasic& other) {
  program_ = other.program_;
  return *this;
}

void PostprocessBasic::init() {
  //TODO

  EDK3::scoped_array<char> error;

  dev::GPUManager::Instance()->newProgram(&program_);

  ref_ptr<EDK3::dev::Shader> vertex_shader;
  ref_ptr<EDK3::dev::Shader> fragment_shader;

  
  dev::GPUManager::Instance()->newShader(&vertex_shader);
  dev::GPUManager::Instance()->newShader(&fragment_shader);

  vertex_shader->loadSource(dev::Shader::kType_Vertex ,kVertexShader, sizeof(kVertexShader));
  fragment_shader->loadSource(dev::Shader::kType_Fragment, kFragmentShader_edge_detection, sizeof(kFragmentShader_edge_detection));
  bool done = false;
  
  /*
  printf("%s\n",kVertexShader);
  */
  printf("%s\n",kFragmentShader_edge_detection);
  done = vertex_shader->compile(&error);
  if(!done)printf("Vertex:\n%s\n", error.get());
  
  done = fragment_shader->compile(&error);
  if(!done)printf("Fragment:\n%s\n", error.get());

  program_->attach(vertex_shader.get());
  program_->attach(fragment_shader.get());

  program_->link();

}

// Render target va a tener una textura asociada al hacer el init
bool PostprocessBasic::enable(const EDK3::MaterialSettings *mat) const {
  //TODO
  //printf("*** Enable postprocess ***\n");
  // Reservamos recursos y los inicializamos
  // llamamos a las cosas del GameState
  // A SetTexture le tenemos que dar lo que nos devuelve el getter ese de Texture sobrecargado
  // El doRender tiene que estar entre el begin y el end

  program_->use();
  const PostprocessBasicSettings *pps = dynamic_cast<const PostprocessBasicSettings*>(mat);

  if (pps){
    int uniform_att = program_->get_uniform_position("u_time");
    float time = (float)ESAT::Time();
    program_->set_uniform_value(uniform_att,EDK3::Type::T_FLOAT, &time);
    
    uniform_att = program_->get_uniform_position("u_color");
    program_->set_uniform_value(uniform_att,EDK3::Type::T_FLOAT_4, pps->color());
    
    int texture_pos = 0;
    pps->texture()->bind(texture_pos);
    uniform_att = program_->get_uniform_position("u_texture");
    program_->set_uniform_value(uniform_att, EDK3::Type::T_INT, &texture_pos);
    
    return true;
  }

  return false;
}

void PostprocessBasic::setupCamera(const float projection[16], const float view[16]) const {
  //TODO
  int attrib_tag = program_->get_uniform_position("u_projection_matrix");
  program_->set_uniform_value(attrib_tag, T_MAT_4x4, projection);
  attrib_tag = program_->get_uniform_position("u_view_matrix");
  program_->set_uniform_value(attrib_tag, T_MAT_4x4, view);
}

void PostprocessBasic::setupModel(const float model[16]) const {
  //TODO
  const int attrib_tag = program_->get_uniform_position("u_model_matrix");
  program_->set_uniform_value(attrib_tag, T_MAT_4x4, model);
}

unsigned int PostprocessBasic::num_attributes_required() const {
  return 3;
}

EDK3::Attribute PostprocessBasic::attribute_at_index(const unsigned int attrib_idx) const {
  //TODO

  switch (attrib_idx){
    case 0: return EDK3::Attribute::A_POSITION; break;
    case 1: return EDK3::Attribute::A_NORMAL; break;
    case 2: return EDK3::Attribute::A_UV; break;
    default: return EDK3::Attribute::A_NONE; break;
  }
}

EDK3::Type PostprocessBasic::attribute_type_at_index(const unsigned int attrib_idx) const {
  //TODO

  switch (attrib_idx){
    case 0: return EDK3::Type::T_FLOAT_3; break;
    case 1: return EDK3::Type::T_FLOAT_3; break;
    case 2: return EDK3::Type::T_FLOAT_2; break;
    default: return EDK3::Type::T_NONE; break;
  }
}

} //EDK3
