#include "geometry_custom_terrain.h"

#include "Perlin/SimplexNoise.h"
#include "oxml/Vec2.h"
#include "oxml/Vec3.h"
#include "EDK3/dev/gpumanager.h"
#include "vertex.h"

namespace EDK3
{
  
  TerrainCustom::TerrainCustom()
  : is_initialized_(false), num_cols_(0), num_rows_(0) {}

  TerrainCustom::~TerrainCustom() {}

  TerrainCustom::TerrainCustom(const TerrainCustom&) {}

  TerrainCustom::TerrainCustom(TerrainCustom&&) {}

  TerrainCustom& TerrainCustom::operator=(const TerrainCustom&)
  {
    return *this;
  }
  
  void TerrainCustom::init (bool *wireframe, const int num_cols, const int num_rows, const float height_mult, const float size, const bool is_centered){
    num_cols_ = num_cols;
    num_rows_ = num_rows;
    is_initialized_ = true;
    wireFrameMode_ = wireframe;
    
    const int num_vertex_x = num_cols + 1;
    const int num_vertex_y = num_rows + 1;

    EDK3::scoped_array<Vertex> vertex_buff;
    EDK3::scoped_array<unsigned int> index_buff;
    
    vertex_buff.alloc(num_vertex_x * num_vertex_y);
    index_buff.alloc(6 * (num_cols * num_rows));

    float delta_uv_x = 1.0f / num_vertex_x;
    float delta_uv_y = 1.0f / num_vertex_y;

    if (is_centered)
    {
      for (int y = 0; y < num_vertex_y; y++)
      {
        for (int x = 0; x < num_vertex_x; x++)
        {
          vertex_buff[x + y * num_vertex_x].pos = {(float)(x - (num_vertex_x / 2)) * size, SimplexNoise::noise(((x - (num_vertex_x / 2)) * size) * 0.1f,((y - (num_vertex_y / 2)) * size) * 0.1f) * height_mult, (float)(y - (num_vertex_y / 2)) * size};
          vertex_buff[x + y * num_vertex_x].uv = {delta_uv_x * x, delta_uv_y * y};
          // TODO (Hector) Hacer UVs

        }
      }
    }
    else
    {
      for (int y = 0; y < num_vertex_y; y++)
      {
        for (int x = 0; x < num_vertex_x; x++)
        {
          vertex_buff[x + y * num_vertex_x].pos = {(float)x * size, SimplexNoise::noise((x * size) * 0.1f, (y * size) * 0.1f) * height_mult, (float)y * size};
          vertex_buff[x + y * num_vertex_x].uv = {delta_uv_x * x, delta_uv_y * y};
          // TODO (Hector) Hacer UVs
        }
      }
    }

    oxml::Vec3 vec1, vec2, result;
    oxml::Vec3 p1,p2,p3,p4;

    int new_;
    
    for (int y = 0; y < num_vertex_y; y ++)
    {
      for (int x = 0; x < num_vertex_x; x++)
      {
        // Vectores entre el medio y los coolindantes
        new_ = (x + 1);
        if (new_ < num_vertex_x)
          p1 = vertex_buff[new_ + y * num_vertex_x].pos;
        else
          p1 = oxml::Vec3((float)new_ * size, 0.0f, (float)y * size);

        new_ = (y - 1);
        if (new_ >= 0)
          p2 = vertex_buff[x + new_ * num_vertex_x].pos;
        else
          p2 = oxml::Vec3((float)x * size, 0.0f, (float)new_ * size);

        new_ = (x - 1);
        if (new_ >= 0)
          p3 = vertex_buff[new_ + y * num_vertex_x].pos;
        else
          p3 = oxml::Vec3((float)new_ * size, 0.0f, (float)y * size);

        new_ = (y + 1);
        if (new_ < num_vertex_y)
          p4 = vertex_buff[x + new_ * num_vertex_x].pos;
        else
          p4 = oxml::Vec3((float)x * size, 0.0f, (float)new_ * size);

      

        vec1 = vertex_buff[x + y * num_vertex_x].pos - p1;
        vec2 = vertex_buff[x + y * num_vertex_x].pos - p2;
        
        result = oxml::Vec3::Cross(vec1, vec2);

        vec1 = vertex_buff[x + y * num_vertex_x].pos - p2;
        vec2 = vertex_buff[x + y * num_vertex_x].pos - p3;

        result += oxml::Vec3::Cross(vec1, vec2);

        vec1 = vertex_buff[x + y * num_vertex_x].pos - p3;
        vec2 = vertex_buff[x + y * num_vertex_x].pos - p4;

        result += oxml::Vec3::Cross(vec1, vec2);

        vec1 = vertex_buff[x + y * num_vertex_x].pos - p4;
        vec2 = vertex_buff[x + y * num_vertex_x].pos - p1;

        result += oxml::Vec3::Cross(vec1, vec2);

        result.Normalize();
        
        vertex_buff[x + y * num_vertex_x].normal = result;
      }
    }

    int index = 0;
    int i = 0;
    for (int y = 0; y < num_rows; y++) {
      for (int x = 0; x < num_cols; x++) {


        i = x + y * num_cols;
        index = i * 6;
        index_buff[index] = i + y + (num_cols + 1);
        index_buff[index + 1] = i + y + 1;
        index_buff[index + 2] = i + y;

        index_buff[index + 3] = i + y + 1 + (num_cols + 1);
        index_buff[index + 4] = i + y + 1;
        index_buff[index + 5] = i + y + (num_cols + 1);
      }
    }
#ifdef DEBUG

    /*for (int i = 0; i < vertex_buff.size(); i++)
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
    }*/
#endif
    dev::GPUManager::Instance()->newBuffer(&elements_buffer);
    dev::GPUManager::Instance()->newBuffer(&order_buffer);
    
    elements_buffer->init(vertex_buff.sizeInBytes());
    order_buffer->init(index_buff.sizeInBytes());

    elements_buffer->uploadData(vertex_buff.get(), vertex_buff.sizeInBytes());
    order_buffer->uploadData(index_buff.get(), index_buff.sizeInBytes());
    
  }

  void TerrainCustom::render() const{
    if(*wireFrameMode_){
      dev::GPUManager::Instance()->drawElements(dev::GPUManager::kDrawMode_Lines, (num_cols_ * num_rows_ * 6), order_buffer.get(), T_UINT);
    }else{
      dev::GPUManager::Instance()->drawElements(dev::GPUManager::kDrawMode_Triangles, (num_cols_ * num_rows_ * 6), order_buffer.get(), T_UINT);
    }
  }

  bool TerrainCustom::bindAttribute
  (
    const Attribute a,
    unsigned where_to_bind_attribute
  ) const
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


  
}
