#pragma once

#include "../renderer.h"
#include <stdint.h>

typedef struct {
  Shader lightingShader;
  uint32_t cubeVao;
  uint32_t cubeVbo;
  uint32_t cubeEbo;
  float near;
  float far;
} RenderState3D;

void initRenderer3D(RenderState *state, float near, float far);
void drawCube(vec3 position, float rotation, vec3 size, vec4 color);
void draw(Shader *shader, uint32_t vao, uint32_t indexCount, mat4x4 transform);
