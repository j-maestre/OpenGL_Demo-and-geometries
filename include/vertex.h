#ifndef __VERTEX__
#define __VERTEX__ 1

#include "oxml/Vec3.h"
#include "oxml/Vec2.h"

namespace EDK3
{

  struct Vertex
  {
    oxml::Vec3 pos;
    oxml::Vec3 normal;
    oxml::Vec2 uv;
  };

}

#endif