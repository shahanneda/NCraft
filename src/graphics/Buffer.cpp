#include "Buffer.h"
#include "../NCraftMain.h"

VertexBuffer::VertexBuffer() : Buffer()
{
  glGenBuffers(1, &bufferId);
  glGenBuffers(1, &elementsBufferId);

  glGenVertexArrays(1, &vertexArrayBufferId);

  BindVertexArrayBuffer(); // we bind the vertex array so it keeps track of all the things were doing
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBufferId);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0); // this is the location for vertex

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1); // this is the location for textures

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

void VertexBuffer::PutVertexData(std::vector<glm::vec3> verts, std::vector<int> indices, std::vector<glm::vec2> textures)
{
  int numberOfElements = verts.size() * 3 + textures.size() * 2;
  float vertsWithTextures[numberOfElements];

  // just for unpacking the arrays
  uint32_t vertexIndex = 0;
  uint32_t textureIndex = 0;
  for (int i = 0; i < verts.size() * 3 + textures.size() * 2; i += 5)
  {
    vertsWithTextures[i] = (float)verts[vertexIndex].x;
    vertsWithTextures[i + 1] = (float)verts[vertexIndex].y;
    vertsWithTextures[i + 2] = (float)verts[vertexIndex].z;
    vertsWithTextures[i + 3] = (float)textures[textureIndex].x;
    vertsWithTextures[i + 4] = (float)textures[textureIndex].y;

    vertexIndex++;
    textureIndex++;
  }

  BindVertexArrayBuffer();
  glBufferData(GL_ARRAY_BUFFER, numberOfElements * sizeof(float), &vertsWithTextures[0], GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
}
