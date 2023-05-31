#include "geometry_custom_sphere.h"

#include <math.h>
#include "EDK3/dev/gpumanager.h"
#include "oxml/Mathf.h"
#include "vertex.h"

namespace EDK3
{
  SphereCustom::SphereCustom() : is_initialized_(false) {}

  SphereCustom::SphereCustom(const SphereCustom&){}
  SphereCustom::SphereCustom(SphereCustom&&){}
  SphereCustom& SphereCustom::operator=(const SphereCustom&) { return  *this; }
  
  SphereCustom::~SphereCustom(){}
  /*
    x = cos(alpha) * cos(omega)
    y = sin(alpha)
    z = cos(alpha) * sin(omega)


    omega = 2*pi / KNrevolutions
    alpha = pi / KNHeights
  */

  void SphereCustom::init(bool *wireframe, const float sphere_size, const int num_heights, const int num_revs)
  {
    
    is_initialized_ = true;
    wireFrameMode_ = wireframe;
    

    num_heights_ = num_heights;
    num_revs_ = num_revs;

    const int num_vertex_x = num_revs_ + 1;
    const int num_vertex_y = num_heights_ + 1;

    const float size = sphere_size / 2.0f;

    const float omega = (2.0f * oxml::Mathf::PI) / num_revs_;
    const float alpha = oxml::Mathf::PI / num_heights_;

    EDK3::scoped_array<Vertex> vertex_buff;
    EDK3::scoped_array<unsigned int> index_buff;

    vertex_buff.alloc(num_vertex_x * num_vertex_y);
    index_buff.alloc(6 * num_heights_ * num_revs_);
    

    // Posicion de los vertices
    for (int y = 0; y < num_vertex_y; y++){
      for(int x = 0; x < num_vertex_x; x++){

          float x_pos = cosf((alpha * y) - 1.5708f) * cosf(omega * x) * size;
          float y_pos = sinf((alpha * y) - 1.5708f) * size;
          float z_pos = cosf((alpha * y) - 1.5708f) * sinf(omega * x) * size;
          vertex_buff[x + y * num_vertex_x].pos = {x_pos, y_pos, z_pos};
          vertex_buff[x + y * num_vertex_x].normal = {x_pos, y_pos, z_pos};
          vertex_buff[x + y * num_vertex_x].normal.Normalize(); 
          vertex_buff[x + y * num_vertex_x].uv = {0.0f, 0.0f};
          printf("[Index] %d\n", x + y * num_vertex_x);
          vertex_buff[x + y * num_vertex_x].uv = {(float) x / num_revs, (float) y / num_heights};
      }
    }
    
    
    // Orden de los vertices
    int index = 0;
    int i = 0;
    for (int y = 0; y < num_heights_; y++) {
      for (int x = 0; x < num_revs_; x++) {
        i = x + y * num_revs_;
        index = i * 6;
        index_buff[index] = i + y + (num_revs_ + 1);
        index_buff[index + 1] = i + y + 1;
        index_buff[index + 2] = i + y;

        index_buff[index + 3] = i + y + 1 + (num_revs_ + 1);
        index_buff[index + 4] = i + y + 1;
        index_buff[index + 5] = i + y + (num_revs_ + 1);
      }
    }

    dev::GPUManager *gpu = dev::GPUManager::Instance();

    gpu->newBuffer(&elements_buffer_);
    gpu->newBuffer(&order_buffer_);

    elements_buffer_->init(vertex_buff.sizeInBytes());
    order_buffer_->init(index_buff.sizeInBytes());

    elements_buffer_->uploadData(vertex_buff.get(), vertex_buff.sizeInBytes());
    order_buffer_->uploadData(index_buff.get(), index_buff.sizeInBytes());


#   ifdef DEBUG
    for (int i = 0; i < vertex_buff.size(); i++)
    {
      printf("Vertex [%d]\n", i);
      printf("[Pos] x: %f, y: %f, z: %f\n", vertex_buff[i].pos.x, vertex_buff[i].pos.y, vertex_buff[i].pos.z);
      printf("[Normal] x: %f, y: %f, z: %f\n", vertex_buff[i].normal.x, vertex_buff[i].normal.y, vertex_buff[i].normal.z);
      printf("[Uv] x: %f, y: %f\n", vertex_buff[i].uv.x, vertex_buff[i].uv.y);
    }

    for (int i = 0; i < index_buff.size(); i += 3)
    {
      printf("Triangle [%d]\n", (i / 3));
      printf("[Index] %d, %d, %d\n", index_buff[i], index_buff[i + 1], index_buff[i + 2]);
    }
#   endif


    

     
  }

  bool SphereCustom::bindAttribute(const Attribute a, unsigned where_to_bind_attribute) const
  {
    switch (a)
    {
      case A_POSITION:
        dev::GPUManager::Instance()->enableVertexAttribute(elements_buffer_.get(), where_to_bind_attribute, Type::T_FLOAT_3, false, 0, sizeof(Vertex));
        break;
      case A_NORMAL:
        dev::GPUManager::Instance()->enableVertexAttribute(elements_buffer_.get(), where_to_bind_attribute, Type::T_FLOAT_3, false, sizeof(oxml::Vec3), sizeof(Vertex));
        break;
      case A_UV:
        dev::GPUManager::Instance()->enableVertexAttribute(elements_buffer_.get(), where_to_bind_attribute, Type::T_FLOAT_2, false, sizeof(oxml::Vec3) * 2, sizeof(Vertex));
        break;
      default:
        return false;
    }
    return true;
  }

  void SphereCustom::render() const{
    if(*wireFrameMode_){
      dev::GPUManager::Instance()->drawElements(dev::GPUManager::kDrawMode_Lines, ((num_heights_) * (num_revs_) * 6),order_buffer_.get(),T_UINT);
    }else{
      dev::GPUManager::Instance()->drawElements(dev::GPUManager::kDrawMode_Triangles, ((num_heights_) * (num_revs_) * 6),order_buffer_.get(),T_UINT);
    }
  }


}

