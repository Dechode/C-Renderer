#pragma once

#include "glad/glad.h"
#include "renderer.h"
#include "linmath.h"
#include <stdint.h>

typedef struct {
  // mat4x4 viewProjectionMat;
  Shader lightingShader;
  uint32_t lightVao;
} RenderState3D;

void initRenderer3D(RenderState *state);
void draw3D(Shader *shader, uint32_t vao, uint32_t indexCount, mat4x4 transform);
