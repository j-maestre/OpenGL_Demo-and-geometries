#include "EDK3/dev/glew.h"
#include "dev/custom_gpu_buffer.h"

EDK3::dev::CustomGPUBuffer::CustomGPUBuffer() {
  size_ = 0;
}

EDK3::dev::CustomGPUBuffer::CustomGPUBuffer(const CustomGPUBuffer&) {

}

EDK3::dev::CustomGPUBuffer& EDK3::dev::CustomGPUBuffer::operator=(const CustomGPUBuffer&) {
  return *this;
}

EDK3::dev::CustomGPUBuffer::~CustomGPUBuffer() {
  glDeleteBuffers(1, &id_);
}

void EDK3::dev::CustomGPUBuffer::init(unsigned int size) {
  size_ = size;
  glGenBuffers(1, &id_);
  glBindBuffer(GL_ARRAY_BUFFER, id_);
  glBufferData(GL_ARRAY_BUFFER, size_, NULL, GL_DYNAMIC_DRAW);
}

void EDK3::dev::CustomGPUBuffer::bind(const Target t) const {
  switch (t)
  {
  case kTarget_Vertex_Data: glBindBuffer(GL_ARRAY_BUFFER, id_); break;
  case kTarget_Elements: glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_); break;
  }
}

unsigned int EDK3::dev::CustomGPUBuffer::size() const {
  return size_;
}

void EDK3::dev::CustomGPUBuffer::uploadData(const void* data, unsigned int size, unsigned int offset) {
  glBindBuffer(GL_ARRAY_BUFFER, id_);
  glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void EDK3::dev::CustomGPUBuffer::release() {
  glDeleteBuffers(1, &id_);
}