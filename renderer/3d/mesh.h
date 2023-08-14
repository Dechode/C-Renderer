#pragma once

#include "../../math/linmath.h"
#include "../../max_values.h"
#include "../../renderer/shader.h"
#include "../../renderer/texture.h"
#include <stdint.h>

typedef struct {
  vec3 positions;
  // vec3 normals;
  vec2 uvs;
} Vertex;

typedef struct {
  Vertex *vertices;
  uint32_t *indices;
  uint32_t vertexCount;
  uint32_t indexCount;
  uint32_t vao;
  uint32_t vbo;
  uint32_t ebo;
  mat4x4 transMat;
} Mesh;

void initMesh(Mesh *mesh, Vertex vertices[], uint32_t indices[],
              uint32_t vertexCount, uint32_t indexCount);

void drawMesh(Mesh *mesh, Shader *shader);
