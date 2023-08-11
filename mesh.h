#pragma once

#include "linmath.h"
#include "max_values.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include <stdint.h>

typedef struct {
  vec3 positions;
  vec3 normals;
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
  Texture texture;
  mat4x4 transMat;
  Transform2D transform2D;
} Mesh;

void initMeshSolidColor(Mesh *mesh, Vertex vertices[], uint32_t indices[],
                        uint32_t vertexCount, uint32_t indexCount);

void initMeshWithTexture(Mesh *mesh, Vertex vertices[], uint32_t indices[],
                         uint32_t vertexCount, uint32_t indexCount,
                         const char *texPath);

void drawMesh(Mesh *mesh, Shader *shader);
