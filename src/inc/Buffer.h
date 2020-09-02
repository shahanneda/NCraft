#ifndef BUFFER
#define BUFFER

#include <Vec3f.h>
#include <vector>

class Buffer
{
public:
  unsigned int bufferId;
  unsigned int vertexArrayBufferId;
  unsigned int elementsBufferId;

  virtual void BindVertexArrayBuffer(){};
};

class VertexBuffer : public Buffer
{
public:
  VertexBuffer();
  void BindVertexArrayBuffer() override;
  void PutVertexData(std::vector<Vec3f> verts, std::vector<int> indices, std::vector<float> textures);
  void UnbindVertexArrayBuffer();
};

#endif