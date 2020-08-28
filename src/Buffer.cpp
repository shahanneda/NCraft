#include <Buffer.h>
#include "inc/NCraftMain.h"

VertexBuffer::VertexBuffer() : Buffer()
{
  glGenBuffers(1, &bufferId);
  glGenBuffers(1, &elementsBufferId);

  glGenVertexArrays(1, &vertexArrayBufferId);

  BindVertexArrayBuffer(); // we bind the vertex array so it keeps track of all the things were doing
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBufferId);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0); // this is the location

  UnbindVertexArrayBuffer(); // so we dont accidently overwrite
}

void VertexBuffer::BindVertexArrayBuffer()
{
  glBindVertexArray(vertexArrayBufferId);
}
void VertexBuffer::UnbindVertexArrayBuffer()
{
  glBindVertexArray(0);
}

void VertexBuffer::PutVertexData(std::vector<Vec3f> verts, std::vector<int> indices)
{
  std::vector<float> vertUnpacked = Vec3f::UnPackArray(verts);
  BindVertexArrayBuffer();

  glBufferData(GL_ARRAY_BUFFER, vertUnpacked.size() * sizeof(float), &vertUnpacked[0], GL_STATIC_DRAW);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
}
