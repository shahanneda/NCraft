#ifndef BUFFER
#define BUFFER

#include <vector>
#include <glm/glm.hpp>

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
  void PutVertexData(std::vector<glm::vec3> verts, std::vector<int> indices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals);
  void UnbindVertexArrayBuffer();
};

#endif