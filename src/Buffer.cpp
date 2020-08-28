#include <Buffer.h>
#include "inc/NCraftMain.h"

VertexBuffer::VertexBuffer() : Buffer()
{
  glGenBuffers(1, &bufferId);
  glGenVertexArrays(1, &vertexArrayBufferId);

  BindVertexArrayBuffer();
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0); // this is the location
}

void VertexBuffer::BindVertexArrayBuffer()
{
  glBindVertexArray(vertexArrayBufferId);
}

void VertexBuffer::PutVertexData(std::vector<Vec3f> verts)
{
  Vec3f::UnPackArray(verts);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verts), &verts[0], GL_STATIC_DRAW);
}
