#pragma once

#include "../material.h"
#include "../renderer.h"
#include "../texture.h"
#include "lighting.h"
#include <stdint.h>

typedef struct {
  Shader lightingShader;
  DirectionalLight sun;
  uint32_t cubeVao;
  uint32_t cubeVbo;
  uint32_t cubeEbo;
  float near;
  float far;
} RenderState3D;

void initRenderer3D(RenderState *state, float vFov, float near, float far);
void drawCube(Material *material, vec3 position, vec3 rotation, float angle,
              vec3 size);
void drawElements(Material *material, vec3 position, vec3 rotation, float angle,
          uint32_t vao, uint32_t indexCount);

void drawArray(Material *material, vec3 position, vec3 rotation, float angle,
          uint32_t vao, uint32_t vertexCount);
RenderState3D *getRenderState3D(void);