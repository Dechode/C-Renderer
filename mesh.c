#include "mesh.h"
#include "glad/glad.h"
#include "renderer_3d.h"
#include "texture.h"
#include <stddef.h>
#include <stdint.h>

void initMeshSolidColor(Mesh *mesh, Vertex vertices[], uint32_t indices[],
                        uint32_t vertexCount, uint32_t indexCount) {

  memcpy(&mesh->vertices, vertices, (size_t)sizeof(Vertex));
  memcpy(&mesh->indices, indices, (size_t)sizeof(uint32_t));
  mesh->vertexCount = vertexCount;
  mesh->indexCount = indexCount;

  glGenVertexArrays(1, &mesh->vao);
  glGenBuffers(1, &mesh->vbo);
  glGenBuffers(1, &mesh->ebo);

  glBindVertexArray(mesh->vao);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

  glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), &vertices[0],
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint32_t),
               &indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, normals));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, uvs));

  initColorTexture(&mesh->texture.id);

  glBindVertexArray(0);
}

void initMeshWithTexture(Mesh *mesh, Vertex vertices[], uint32_t indices[],
                         uint32_t vertexCount, uint32_t indexCount,
                         const char *texPath) {

  initImageTexture(&mesh->texture, texPath);
  memcpy(&mesh->vertices, vertices, (size_t)sizeof(Vertex));
  memcpy(&mesh->indices, indices, (size_t)sizeof(uint32_t));
  mesh->vertexCount = vertexCount;
  mesh->indexCount = indexCount;

  glGenVertexArrays(1, &mesh->vao);
  glGenBuffers(1, &mesh->vbo);
  glGenBuffers(1, &mesh->ebo);

  glBindVertexArray(mesh->vao);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

  glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), &vertices[0],
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint32_t),
               &indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, normals));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, uvs));

  glBindVertexArray(0);
}

void drawMesh(Mesh *mesh, Shader *shader) {
  draw3D(shader, mesh->vao, mesh->indexCount, mesh->transMat);
}