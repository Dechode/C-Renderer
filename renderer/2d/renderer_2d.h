#pragma once

#include "../../glad/glad.h"
#include "../../math/linmath.h"
#include "../shader.h"
#include "../texture.h"

typedef struct {
  uint32_t quadVao;
  uint32_t quadVbo;
  uint32_t quadEbo;

  uint32_t lineVao;
  uint32_t lineVbo;

  uint32_t triangleVao;
  uint32_t triangleVbo;
} RenderState2D;

void initTriangle(uint32_t *vao, uint32_t *vbo);
void initQuad(uint32_t *vao, uint32_t *vbo, uint32_t *ebo);
void initLine(uint32_t *vao, uint32_t *vbo);
void initRenderer2D(void);

void drawLine(Shader *shader, uint32_t textureID, vec2 start, vec2 end,
              vec4 color, int lineWidth);
void drawQuadLine(Shader *shader, uint32_t textureID, vec2 pos, vec2 size,
                  vec4 color, int lineWidth);
void drawQuad(Shader *shader, Texture *texture, vec3 pos, float rotation,
              vec2 size, vec4 color);
void drawCircle(Shader *shader, Texture *texture, vec3 pos, float radius,
                vec4 color);
void drawTriangle(Shader *shader, Texture *texture, vec3 pos, float rotation,
                  vec2 size, vec4 color);
