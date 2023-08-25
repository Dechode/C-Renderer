#include "mesh.h"
#include "../texture.h"
#include "renderer_3d.h"
#include <stddef.h>
#include <stdint.h>

void initMesh(Mesh *mesh, Vertex vertices[], uint32_t indices[],
              uint32_t vertexCount, uint32_t indexCount) {

  if (!vertexCount) {
    printf("No vertice data found when initializing mesh!\n");
    return;
  }
  // memcpy((void*)&mesh->vertices, vertices, (size_t)sizeof(Vertex) * vertexCount);

  // if (indexCount <= 0) {
    // printf("No index data found when initializing mesh!\n");
    // return;
  // }
  // memcpy((void*)&mesh->indices, indices, (size_t)sizeof(uint32_t) * indexCount);

  mesh->indexCount = indexCount;
  mesh->vertexCount = vertexCount;

  glGenVertexArrays(1, &mesh->vao);
  glGenBuffers(1, &mesh->vbo);
  glGenBuffers(1, &mesh->ebo);

  glBindVertexArray(mesh->vao);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

  glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), &vertices[0],
               GL_STATIC_DRAW);

  if (indexCount) {

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint32_t),
                 &indices[0], GL_STATIC_DRAW);
  }

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);
}

void drawMesh(Mesh *mesh, Material *material, vec3 position, vec3 rotation,
              float angle) {
  drawArray(material, position, rotation, angle, mesh->vao, mesh->vertexCount);
}
