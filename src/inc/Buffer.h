#ifndef BUFFER
#define BUFFER

#include <Vec3f.h>
#include <vector>

class Buffer
{
public:
  unsigned int bufferId;
  unsigned int vertexArrayBufferId;

  virtual void BindVertexArrayBuffer(){};
};

class VertexBuffer : public Buffer
{
public:
  VertexBuffer();
  void BindVertexArrayBuffer() override;
  void PutVertexData(std::vector<Vec3f> verts);
};

#endif