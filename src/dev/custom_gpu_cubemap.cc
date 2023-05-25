#include "custom_gpu_cubemap.h"
#include "EDK3/dev/glew.h"
#include "stbi_image.h"
#include "EDK3/dev/gpumanager.h"

CustomGPUCubeMap::CustomGPUCubeMap() {
  id_ = -1;
}
CustomGPUCubeMap::~CustomGPUCubeMap() {
  glDeleteTextures(1, &id_);
}

void CustomGPUCubeMap::init(std::vector<std::string> text) {

  glGenTextures(1, &id_);
  glBindTexture(GL_TEXTURE_CUBE_MAP, id_);
  
  for (unsigned int i = 0; i < text.size(); i++)
  {
    unsigned char* data = stbi_load(text[i].c_str(), &w_, &h_, &n_, 0);
    if (data)
    {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
        0, GL_RGB, w_, h_, 0, GL_RGB, GL_UNSIGNED_BYTE, data
      );
      stbi_image_free(data);
    }

  }
  
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}


void CustomGPUCubeMap::bind(unsigned int textUnit) const {

  glActiveTexture(GL_TEXTURE0 + textUnit);
  glBindTexture(GL_TEXTURE_CUBE_MAP, id_);
}