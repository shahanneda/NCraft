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

void VertexBuffer::PutVertexData(std::vector<Vec3f> verts, std::vector<int> indices, std::vector<float> textures)
{
  std::vector<float> vertsWithTextures(verts.size() * 3 + textures.size());

  // just for unpacking the arrays
  uint32_t vertexIndex = 0;
  uint32_t textureIndex = 0;
  for (int i = 0; i < verts.size() * 3 + textures.size(); i += 5)
  {
    vertsWithTextures[i] = verts[vertexIndex].x;
    vertsWithTextures[i + 1] = verts[vertexIndex].y;
    vertsWithTextures[i + 2] = verts[vertexIndex].z;
    vertsWithTextures[i + 3] = textures[textureIndex];
    vertsWithTextures[i + 4] = textures[textureIndex + 1];

    vertexIndex++;
    textureIndex += 2;
  }

  std::cout << vertsWithTextures.size() << std::endl;
  for (float f : vertsWithTextures)
  {
    std::cout << f << " ";
  }
  std::cout << "after " << std::endl;

  BindVertexArrayBuffer();
  glBufferData(GL_ARRAY_BUFFER, vertsWithTextures.size() * sizeof(float), &vertsWithTextures[0], GL_STATIC_DRAW);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
}
