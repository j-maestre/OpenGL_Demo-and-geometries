#include "geometry_custom_surface.h"

#include <math.h>
#include "EDK3/dev/gpumanager.h"
#include "oxml/Mathf.h"
#include "vertex.h"

namespace EDK3
{
	SurfaceCustom::SurfaceCustom()
	{

	}

  SurfaceCustom::SurfaceCustom(const SurfaceCustom&)
  {

  }
  SurfaceCustom::SurfaceCustom(SurfaceCustom&&){}
  SurfaceCustom& SurfaceCustom::operator=(const SurfaceCustom&) { return *this; }

  SurfaceCustom::~SurfaceCustom(){}

  void SurfaceCustom::init(const float* surface_points, const int num_heights, const int num_revs, bool inverted){
    this->num_heights_ = num_heights;
    this->num_revs_ = num_revs;

		const int num_vertex_x = num_revs_ + 1;
		const int num_vertex_y = num_heights_;

		const float omega = (2.0f * oxml::Mathf::PI) / num_revs_;
		const float alpha = oxml::Mathf::PI / num_heights_;

		EDK3::scoped_array<Vertex> vertex_buff;
		EDK3::scoped_array<unsigned int> index_buff;

		vertex_buff.alloc(num_vertex_x * num_vertex_y);
		index_buff.alloc(6 * num_heights_ * num_revs_);

		for (int y = 0; y < num_vertex_y; y++) {
      for (int x = 0; x < num_vertex_x; x++) {
          float theta = omega * x;  // Ángulo de rotación
          float x_pos = surface_points[0 + (y * 2)] * sinf(theta);
          float y_pos = surface_points[1 + (y * 2)];
          float z_pos = surface_points[0 + (y * 2)] * cosf(theta);
          vertex_buff[x + y * num_vertex_x].pos = { x_pos, y_pos, z_pos };
          //vertex_buff[x + y * num_vertex_x].normal = { sinf(theta), 0.0f, -cosf(theta) };
          //vertex_buff[x + y * num_vertex_x].normal = { x_pos, y_pos, z_pos };
          //vertex_buff[x + y * num_vertex_x].normal.Normalize();
          vertex_buff[x + y * num_vertex_x].uv = { 0.0f, 0.0f };
      }
    }

    oxml::Vec3 vec1, vec2, result;

    int new_;

    // Normales
   for (int y = 0; y < num_heights; y++){
      for (int x = 0; x < num_revs; x++){

        oxml::Vec3 izquierda, arriba, derecha, abajo;

        // En medio
        if((y > 0 && y < num_heights-1) && (x > 0 && x < num_revs-1)){
          izquierda =  vertex_buff[x + y * num_revs].pos - vertex_buff[(x - 1) + y * num_revs].pos;
          derecha   =  vertex_buff[x + y * num_revs].pos - vertex_buff[(x + 1) + y * num_revs].pos;
          abajo     =  vertex_buff[x + y * num_revs].pos - vertex_buff[x + (y + 1) * num_revs].pos;
          arriba    =  vertex_buff[x + y * num_revs].pos - vertex_buff[x + (y - 1) * num_revs].pos;

          result = oxml::Vec3::Cross(derecha, arriba);
          result += oxml::Vec3::Cross(izquierda, abajo);
        }else{

          // Laterales 

          // Arriba 
          /*if(y == 0 && x > 0 && x < num_revs-1){
            izquierda =  vertex_buff[x + y * num_revs].pos - vertex_buff[(x - 1) + y * num_revs].pos;
            derecha   =  vertex_buff[x + y * num_revs].pos - vertex_buff[(x + 1) + y * num_revs].pos;
            abajo     =  vertex_buff[x + y * num_revs].pos - vertex_buff[x + (y + 1) * num_revs].pos;
            result = oxml::Vec3::Cross(derecha, abajo);
            result += oxml::Vec3::Cross(izquierda, abajo);
          }

          // Abajo
          if(y == num_heights-1 && x > 0 && x < num_revs-1){
            izquierda =  vertex_buff[x + y * num_revs].pos - vertex_buff[(x - 1) + y * num_revs].pos;
            derecha   =  vertex_buff[x + y * num_revs].pos - vertex_buff[(x + 1) + y * num_revs].pos;
            arriba    =  vertex_buff[x + y * num_revs].pos - vertex_buff[x + (y - 1) * num_revs].pos;
            result = oxml::Vec3::Cross(derecha, arriba);
            result += oxml::Vec3::Cross(izquierda, arriba);
          }

          // Izqueirda
          if(x == 0 && y > 0 && y < num_heights-1){
            derecha   =  vertex_buff[x + y * num_revs].pos - vertex_buff[(x + 1) + y * num_revs].pos;
            abajo     =  vertex_buff[x + y * num_revs].pos - vertex_buff[x + (y + 1) * num_revs].pos;
            arriba    =  vertex_buff[x + y * num_revs].pos - vertex_buff[x + (y - 1) * num_revs].pos;

            result = oxml::Vec3::Cross(derecha, arriba);
            result += oxml::Vec3::Cross(derecha, abajo);
          }

          // Derecha
          if(x == num_revs-1 && y > 0 && y < num_heights-1){
            izquierda =  vertex_buff[x + y * num_revs].pos - vertex_buff[(x - 1) + y * num_revs].pos;
            abajo     =  vertex_buff[x + y * num_revs].pos - vertex_buff[x + (y + 1) * num_revs].pos;
            arriba    =  vertex_buff[x + y * num_revs].pos - vertex_buff[x + (y - 1) * num_revs].pos;

            result = oxml::Vec3::Cross(izquierda, arriba);
            result += oxml::Vec3::Cross(izquierda, abajo);
          }

          // Esquinas

          // Arriba izquierda
          if(x == 0 && y == 0){
            derecha   =  vertex_buff[x + y * num_revs].pos - vertex_buff[(x + 1) + y * num_revs].pos;
            abajo     =  vertex_buff[x + y * num_revs].pos - vertex_buff[x + (y + 1) * num_revs].pos;
            result = oxml::Vec3::Cross(derecha, abajo);
          }
          
          // Arriba derecha
          if(x == num_revs-1 && y == 0){
            izquierda =  vertex_buff[x + y * num_revs].pos - vertex_buff[(x - 1) + y * num_revs].pos;
            abajo     =  vertex_buff[x + y * num_revs].pos - vertex_buff[x + (y + 1) * num_revs].pos;
            result = oxml::Vec3::Cross(izquierda, abajo);
          }
          
          // Abajo izquierda
          if(x == 0 && y == num_heights-1){
            derecha   =  vertex_buff[x + y * num_revs].pos - vertex_buff[(x + 1) + y * num_revs].pos;
            arriba    =  vertex_buff[x + y * num_revs].pos - vertex_buff[x + (y - 1) * num_revs].pos;
            result = oxml::Vec3::Cross(derecha, arriba);
          }
          
          // Abajo derecha
          if(x == num_revs-1 && y == num_heights-1){
            izquierda =  vertex_buff[x + y * num_revs].pos - vertex_buff[(x - 1) + y * num_revs].pos;
            arriba    =  vertex_buff[x + y * num_revs].pos - vertex_buff[x + (y - 1) * num_revs].pos;
            result = oxml::Vec3::Cross(izquierda, arriba);
          }*/


        
        }

 
        if(result.Magnitude() == 0.0f){
          
          if(y == 0){
            result = {0.0f, 1.0f, 0.0f};
          }else{
            result = {0.0f, -1.0f, 0.0f};
          }
        }

        if(result.x == 0 && result.y == 0 && result.z == 0){
          printf("\033[0;31m");
          printf("[Cuidao]");
          printf("\033[0m");
        }
        //printf("Result x:%f y:%f z:%f\n",result.x, result.y, result.z);
        
        result.Normalize();
        vertex_buff[x + y * num_vertex_x].normal = result;
      }
    }

    // Order 
		int index = 0;
		int i = 0;

    if(!inverted){
      // Normal surface
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
    }else{
      // Surface revolution like a donut
      for (int y = 0; y < num_heights_; y++) {
        for (int x = 0; x < num_revs_; x++) {
          i = x + y * num_revs_;
          index = i * 6;
          index_buff[index + 5] = i + y + (num_revs_ + 1);
          index_buff[index + 4] = i + y + 1;
          index_buff[index + 3] = i + y;

          index_buff[index + 2] = i + y + 1 + (num_revs_ + 1);
          index_buff[index + 1] = i + y + 1;
          index_buff[index] = i + y + (num_revs_ + 1);
        }
      }
    }

    dev::GPUManager* gpu = dev::GPUManager::Instance();

    gpu->newBuffer(&elements_buffer);
    gpu->newBuffer(&order_buffer);

    elements_buffer->init(vertex_buff.sizeInBytes());
    order_buffer->init(index_buff.sizeInBytes());

    elements_buffer->uploadData(vertex_buff.get(), vertex_buff.sizeInBytes());
    order_buffer->uploadData(index_buff.get(), index_buff.sizeInBytes());
	}

  bool SurfaceCustom::bindAttribute(const Attribute a, unsigned where_to_bind_attribute) const
  {
    switch (a)
    {
    case A_POSITION:
      dev::GPUManager::Instance()->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute, Type::T_FLOAT_3, false, 0, sizeof(Vertex));
      break;
    case A_NORMAL:
      dev::GPUManager::Instance()->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute, Type::T_FLOAT_3, false, sizeof(oxml::Vec3), sizeof(Vertex));
      break;
    case A_UV:
      dev::GPUManager::Instance()->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute, Type::T_FLOAT_2, false, sizeof(oxml::Vec3) * 2, sizeof(Vertex));
      break;
    default:
      return false;
    }
    return true;
  }

  void SurfaceCustom::render() const {
    dev::GPUManager::Instance()->drawElements(dev::GPUManager::kDrawMode_Triangles, ((num_heights_) * (num_revs_) * 6), order_buffer.get(), T_UINT);
  }
}