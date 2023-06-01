#include "geometry_custom_cube.h"

#include "EDK3/dev/glew.h"
#include "ESAT/math.h"
#include "EDK3/dev/gpumanager.h"

namespace EDK3
{

  CubeCustom::CubeCustom() {}

  CubeCustom::~CubeCustom() {}

  CubeCustom::CubeCustom(const CubeCustom&) {}

  CubeCustom& CubeCustom::operator=(const CubeCustom&)
  {
    return *this;
  }
  
void CubeCustom::init(const float cube_size, const bool is_packed, bool is_cube_map){
  const float size = cube_size * 0.5f;
  is_cube_map_ = is_cube_map;
  float kBasicCubeSNVertex[] = {
    -size, size, -size,           // v top left front
    -0.577f, 0.577f,  -0.577f,    // vn
    0.0f, 0.0f,                   // vt
    
    size, size, -size,            // v top right front
    0.577f, 0.577f,  -0.577f,     // vn
    1.0f, 0.0f,                   // vt
    
    -size, -size, -size,          // v down left front
    -0.577f, -0.577f,  -0.577f,   // vn
    0.0f, 0.0f,                   // vt
    
    size, -size, -size,           // v down right front
    0.577f, -0.577f,  -0.577f,    // vn
    1.0f, 0.0f,                   // vt
    
    -size, size, size,            // v top left back
    -0.577f, 0.577f,  0.577f,     // vn
    0.0f, 1.0f,                   // vt
    
    size, size, size,             // v top right back
    0.577f, 0.577f,  0.577f,      // vn
    1.0f, 1.0f,                   // vt
    
    -size, -size, size,           // v down left back
    -0.577f, -0.577f,  0.577f,    // vn
    0.0f, 1.0f,                   // vt
    
    size, -size, size,            // v down right back
    0.577f, -0.577f,  0.577f,     // vn
    1.0f, 1.0f                    // vt
  };
    
  unsigned int kBasicCubeSNIndex[] = {
    0, 1, 2, // f front
    2, 1, 3,
    
    1, 5, 3, // f right
    3, 5, 7,
    
    4, 0, 6, // f left
    6, 0, 2,
    
    4, 5, 0, // f top
    0, 5, 1,
    
    2, 7, 6, // f down
    3, 7, 2,
    
    5, 4, 7, // f back
    7, 4, 6
  };

  float kBasicCubeVertex[] = {
    -size, size, -size,           // v top left front
    0.0f, 0.0f, -1.0f,            // vn
    0.0f, 1.0f,                   // vt
    
    -size, size, -size,           // v top left front
    -1.0f, 0.0f, 0.0f,            // vn
    1.0f, 1.0f,                   // vt
    
    -size, size, -size,           // v top left front
    0.0f, 1.0f, 0.0f,             // vn
    1.0f, 1.0f,                   // vt
    
    size, size, -size,            // v top right front
    0.0f, 0.0f, -1.0f,            // vn
    1.0f, 1.0f,                   // vt
    
    size, size, -size,            // v top right front
    1.0f, 0.0f, 0.0f,             // vn
    0.0f, 1.0f,                   // vt
    
    size, size, -size,            // v top right front
    0.0f, 1.0f, 0.0f,             // vn
    0.0f, 1.0f,                   // vt
    
    -size, -size, -size,          // v down left front
    0.0f, 0.0f, -1.0f,            // vn
    0.0f, 0.0f,                   // vt
    
    -size, -size, -size,          // v down left front
    -1.0f, 0.0f, 0.0f,            // vn
    1.0f, 0.0f,                   // vt
    
    -size, -size, -size,          // v down left front
    0.0f, -1.0f, 0.0f,            // vn
    1.0f, 0.0f,                   // vt
    
    size, -size, -size,           // v down right front
    0.0f, 0.0f, -1.0f,            // vn
    1.0f, 0.0f,                   // vt

    size, -size, -size,           // v down right front
    1.0f, 0.0f, 0.0f,             // vn
    0.0f, 0.0f,                   // vt

    size, -size, -size,           // v down right front
    0.0f, -1.0f, 0.0f,            // vn
    0.0f, 0.0f,                   // vt
    
    -size, size, size,            // v top left back
    -1.0f, 0.0f, 0.0f,            // vn
    0.0f, 1.0f,                   // vt

    -size, size, size,            // v top left back
    0.0f, 1.0f, 0.0f,             // vn
    1.0f, 0.0f,                   // vt

    -size, size, size,            // v top left back
    0.0f, 0.0f, 1.0f,             // vn
    1.0f, 1.0f,                   // vt
    
    size, size, size,             // v top right back
    1.0f, 0.0f, 0.0f,             // vn
    1.0f, 1.0f,                   // vt

    size, size, size,             // v top right back
    0.0f, 1.0f, 0.0f,             // vn
    0.0f, 0.0f,                   // vt

    size, size, size,             // v top right back
    0.0f, 0.0f, 1.0f,             // vn
    0.0f, 1.0f,                   // vt
    
    -size, -size, size,           // v down left back
    -1.0f, 0.0f, 0.0f,            // vn
    0.0f, 0.0f,                   // vt

    -size, -size, size,           // v down left back
    0.0f, -1.0f, 0.0f,            // vn
    1.0f, 1.0f,                   // vt

    -size, -size, size,           // v down left back
    0.0f, 0.0f, 1.0f,             // vn
    1.0f, 0.0f,                   // vt
    
    size, -size, size,            // v down right back
    1.0f, 0.0f, 0.0f,             // vn
    1.0f, 0.0f,                   // vt

    size, -size, size,            // v down right back
    0.0f, -1.0f, 0.0f,            // vn
    0.0f, 1.0f,                   // vt

    size, -size, size,            // v down right back
    0.0f, 0.0f, 1.0f,             // vn
    0.0f, 0.0f                    // vt
  };
    
  unsigned int kBasicCubeIndex[] = {
    0, 3, 6,                    // f front
    6, 3, 9,
    
    3 + 1, 15, 9 + 1,          // f right
    9 + 1, 15, 21,
    
    12, 0 + 1, 18,              // f left
    18, 0 + 1, 6 + 1,
    
    12 + 1, 15 + 1, 0 + 2,      // f top
    0 + 2, 15 + 1, 3 + 2,
    
    6 + 2, 21 + 1, 18 + 1,      // f down 
    9 + 2, 21 + 1, 6 + 2,
    
    15 + 2, 12 + 2, 21 + 2,     // f back
    21 + 2, 12 + 2, 18 + 2
  };
    
  dev::GPUManager *gpu = dev::GPUManager::Instance();

  gpu->newBuffer(&elements_buffer);
  gpu->newBuffer(&order_buffer);
    
  if (is_packed)
  {
    elements_buffer->init(sizeof(kBasicCubeSNVertex));
    elements_buffer->uploadData(kBasicCubeSNVertex, sizeof(kBasicCubeSNVertex), 0);

    order_buffer->init(sizeof(kBasicCubeSNIndex));
    order_buffer->uploadData(kBasicCubeSNIndex, sizeof(kBasicCubeSNIndex), 0);
  }
  else
  {
    elements_buffer->init(sizeof(kBasicCubeVertex));
    elements_buffer->uploadData(kBasicCubeVertex, sizeof(kBasicCubeVertex), 0);

    order_buffer->init(sizeof(kBasicCubeIndex));
    order_buffer->uploadData(kBasicCubeIndex, sizeof(kBasicCubeIndex), 0);
  }
  
}
    
bool CubeCustom::bindAttribute(const Attribute a, unsigned where_to_bind_attribute) const
{
    dev::GPUManager *gpu = dev::GPUManager::Instance(); 
  switch (a)
  {
  case A_POSITION:
    gpu->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute, T_FLOAT_3, false, 0, 8 * sizeof(float));
    break;
  case A_NORMAL:
    gpu->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute, T_FLOAT_3, false, 3 * sizeof(float), 8 * sizeof(float));
    break;
  case A_UV:
    gpu->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute, T_FLOAT_2, false, 6 * sizeof(float), 8 * sizeof(float));
    break;
  default:
    return false;
  }
    return true;
}

  void CubeCustom::render() const
  {
    dev::GPUManager *gpu = dev::GPUManager::Instance();
    if (is_cube_map_)
    {
      glCullFace(GL_FRONT);
    }

    gpu->drawElements(dev::GPUManager::kDrawMode_Triangles, 36, order_buffer.get(), T_UINT);
    
    if (is_cube_map_)
    {
      gpu->changeDepthMask();
      gpu->enableDepthTest(dev::GPUManager::kCompareFunc_Less);
      glCullFace(GL_BACK);
    }
  }





  
}
