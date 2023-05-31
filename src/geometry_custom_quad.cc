/**
 *
 * @brief Custom quad source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */

#include "geometry_custom_quad.h"
#include "ESAT/math.h"
#include "EDK3/dev/gpumanager.h"


namespace EDK3 {

//IMPORTANT!!!
//TODO constructors, destructor and =operator here!!!

QuadCustom::QuadCustom() {}
  
QuadCustom::QuadCustom(const QuadCustom&){}

QuadCustom& QuadCustom::operator=(const QuadCustom&)
{
  return *this;
}

QuadCustom::~QuadCustom() {}

  
void QuadCustom::init(bool *wireframe, const float quad_size) {
  //TODO demand graphic resources to the GPUManager.

  /**
   The quad face is like this:
         ------------
         |\        |
         | \       |
         |  \      |
         |   \     |
         |    \    |
         |     \   |
         |      \  |
         |       \ |
         |        \|
         ------------
    That's the order of its face.
   */
  wireFrameMode_ = wireframe;
  dev::GPUManager *instance = dev::GPUManager::Instance();
  
  instance->newBuffer(&elements_buffer);
  instance->newBuffer(&order_buffer);

  const float size = quad_size * 0.5f;
  
  float kBasicQuadVertex[] = {
    -size, size, 0.0f,    // v
    0.0f, 0.0f, -1.0f,    // vn
    0.0f, 1.0f,           // vt
    -size, -size, 0.0f,   // v
    0.0f, 0.0f, -1.0f,    // vn
    0.0f, 0.0f,           // vt
    size, -size, 0.0f,    // v
    0.0f, 0.0f, -1.0f,    // vn
    1.0f, 0.0f,           // vt
    size, size, 0.0f,     // v
    0.0f, 0.0f, -1.0f,    // vn
    1.0f, 1.0f            // vt

  };

  unsigned int kBasicQuadIndex[] = {
    0, 1, 2,
    2, 3, 0
  };
  
  //****** Upload data:
  //TODO initialize and upload data to the "elements_buffer".
  //Size in bytes: 12 data per element * 1 faces * 4 vertices per face * sizeof(float)
  //48 attributes has a face.
  elements_buffer->init(sizeof(kBasicQuadVertex));

  elements_buffer->uploadData(kBasicQuadVertex, sizeof(kBasicQuadVertex), 0);
  
  //****** Upload order:
  //TODO initialize and upload data to the "order_buffer".
  //Remember to order triangles in counter clockwise direction!!
  //6 vertices per face * 1 faces * sizeof(short int)

  order_buffer->init(sizeof(kBasicQuadIndex));

  order_buffer->uploadData(kBasicQuadIndex, sizeof(kBasicQuadIndex), 0);
  
}

bool QuadCustom::bindAttribute(const Attribute a,
                               unsigned int where_to_bind_attribute) const {
  EDK3::dev::GPUManager *gpu_manager = EDK3::dev::GPUManager::Instance();
  switch (a)
  {
  case A_POSITION:
    gpu_manager->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute, T_FLOAT_3, false, 0, 8 * sizeof(float));
    break;
  case A_NORMAL:
    gpu_manager->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute, T_FLOAT_3, false, sizeof(ESAT::Vec3), 8 * sizeof(float));
    break;
  case A_UV:
    gpu_manager->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute, T_FLOAT_2, false, 2 * sizeof(ESAT::Vec3), 8 * sizeof(float));
    break;
  default:
    return false;
  }
  return true;
}

void QuadCustom::render() const {
  //TODO
  if(*wireFrameMode_){
    EDK3::dev::GPUManager::Instance()->drawElements(dev::GPUManager::kDrawMode_Lines, 6, order_buffer.get(), T_UINT);
  }else{ 
    EDK3::dev::GPUManager::Instance()->drawElements(dev::GPUManager::kDrawMode_Triangles, 6, order_buffer.get(), T_UINT);
  }
}

  
} //EDK3
