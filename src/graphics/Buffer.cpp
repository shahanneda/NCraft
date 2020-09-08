#include "Buffer.h"
#include "../NCraftMain.h"

void Buffer::BindVertexArrayBuffer()
{
  glBindVertexArray(vertexArrayBufferId);
}
void VertexBuffer::BindVertexArrayBuffer()
{
  glBindVertexArray(vertexArrayBufferId);
}
void Buffer::UnbindVertexArrayBuffer()
{
  glBindVertexArray(0);
}

VertexBuffer::VertexBuffer() : Buffer()
{
  glGenBuffers(1, &bufferId);
  glGenBuffers(1, &elementsBufferId);

  glGenVertexArrays(1, &vertexArrayBufferId);

  BindVertexArrayBuffer(); // we bind the vertex array so it keeps track of all the things were doing
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBufferId);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0); // not shifted
  glEnableVertexAttribArray(0);                                                  // this is the location for vertex

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float))); // shifted by 3 since 3 verts
  glEnableVertexAttribArray(1);                                                                    // this is the location for textures

  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float))); // shifte by 5 since 3 verts + 2 text
  glEnableVertexAttribArray(2);                                                                    // this is the location for normals

  UnbindVertexArrayBuffer(); // so we dont accidently overwrite
}

void VertexBuffer::PutVertexData(std::vector<glm::vec3> verts, std::vector<int> indices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals)
{
  int numberOfElements = verts.size() * 3 + textures.size() * 2 + normals.size() * 3;
  float *vertsWithTextures = new float[numberOfElements]; // manually allocating array instead of vector for preformance

  // just for unpacking the arrays
  uint32_t vertexIndex = 0;
  uint32_t textureIndex = 0;
  for (int i = 0; i < numberOfElements; i += 8)
  {
    // Verts
    vertsWithTextures[i] = (float)verts[vertexIndex].x;
    vertsWithTextures[i + 1] = (float)verts[vertexIndex].y;
    vertsWithTextures[i + 2] = (float)verts[vertexIndex].z;

    //textures
    vertsWithTextures[i + 3] = (float)textures[textureIndex].x;
    vertsWithTextures[i + 4] = (float)textures[textureIndex].y;

    //normals
    vertsWithTextures[i + 5] = normals[vertexIndex].x;
    vertsWithTextures[i + 6] = normals[vertexIndex].y;
    vertsWithTextures[i + 7] = normals[vertexIndex].z;

    vertexIndex++;
    textureIndex++;
  }

  BindVertexArrayBuffer();
  glBufferData(GL_ARRAY_BUFFER, numberOfElements * sizeof(float), &vertsWithTextures[0], GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
  delete[] vertsWithTextures;
}

UIBuffer::UIBuffer() : Buffer()
{
  glGenBuffers(1, &bufferId);
  glGenBuffers(1, &elementsBufferId);

  glGenVertexArrays(1, &vertexArrayBufferId);

  BindVertexArrayBuffer(); // we bind the vertex array so it keeps track of all the things were doing
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBufferId);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0); // not shifted
  glEnableVertexAttribArray(0);                                                  // this is the location for vertex

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float))); // shifted by 3 since 3 verts
  glEnableVertexAttribArray(1);                                                                    // this is the location for textures

  UnbindVertexArrayBuffer(); // so we dont accidently overwrite
}

void UIBuffer::PutVertexData(std::vector<glm::vec3> verts, std::vector<int> indices, std::vector<glm::vec2> textures)
{
  int numberOfElements = verts.size() * 3 + textures.size() * 2;
  float *vertsWithTextures = new float[numberOfElements]; // manually allocating array instead of vector for preformance

  // just for unpacking the arrays
  uint32_t vertexIndex = 0;
  uint32_t textureIndex = 0;
  for (int i = 0; i < numberOfElements; i += 5)
  {
    // Verts
    vertsWithTextures[i] = (float)verts[vertexIndex].x;
    vertsWithTextures[i + 1] = (float)verts[vertexIndex].y;
    vertsWithTextures[i + 2] = (float)verts[vertexIndex].z;

    //textures
    vertsWithTextures[i + 3] = (float)textures[textureIndex].x;
    vertsWithTextures[i + 4] = (float)textures[textureIndex].y;

    vertexIndex++;
    textureIndex++;
  }

  BindVertexArrayBuffer();
  glBufferData(GL_ARRAY_BUFFER, numberOfElements * sizeof(float), &vertsWithTextures[0], GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
  delete[] vertsWithTextures;
}
