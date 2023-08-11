#include "renderer_2d.h"
#include "glad/glad.h"
#include "shader.h"
#include <stdint.h>
#include <stdio.h>

static RenderState2D _state2D;
// RenderState2D _state2D;

void initTriangle(uint32_t *vao, uint32_t *vbo) {
  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

  glGenVertexArrays(1, vao);
  glGenBuffers(1, vbo);
  glBindVertexArray(*vao);
  glBindBuffer(GL_ARRAY_BUFFER, *vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void initQuad(uint32_t *vao, uint32_t *vbo, uint32_t *ebo) {
  float vertices[] = {0.5,  0.5,  0, 0, 0, 0.5,  -0.5, 0, 0, 1,
                      -0.5, -0.5, 0, 1, 1, -0.5, 0.5,  0, 1, 0};

  uint32_t indices[] = {0, 1, 3, 1, 2, 3};

  glGenVertexArrays(1, vao);
  glGenBuffers(1, vbo);
  glGenBuffers(1, ebo);

  glBindVertexArray(*vao);

  glBindBuffer(GL_ARRAY_BUFFER, *vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void initLine(uint32_t *vao, uint32_t *vbo) {
  glGenVertexArrays(1, vao);
  glBindVertexArray(*vao);

  glGenBuffers(1, vbo);
  glBindBuffer(GL_ARRAY_BUFFER, *vbo);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), NULL, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

void initRenderer2D(void) {
  initTriangle(&_state2D.triangleVao, &_state2D.triangleVbo);
  initQuad(&_state2D.quadVao, &_state2D.quadVbo, &_state2D.quadEbo);
  initLine(&_state2D.lineVao, &_state2D.lineVbo);

  puts("2D Renderer initialized");
}

void drawLine(Shader *shader, uint32_t textureID, vec2 start, vec2 end,
              vec4 color, int lineWidth) {

  bindShader(shader->id);
  glLineWidth(lineWidth);

  float x = end[0] - start[0];
  float y = end[1] - start[1];
  float line[6] = {0, 0, 0, x, y, 0};

  mat4x4 model;
  mat4x4_translate(model, start[0], start[1], 0);

  setMat4(shader, "model", model);
  setFloat4(shader, "color", color);

  glBindTexture(GL_TEXTURE_2D, textureID);
  glBindVertexArray(_state2D.lineVao);

  glBindBuffer(GL_ARRAY_BUFFER, _state2D.lineVbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(line), line);
  glDrawArrays(GL_LINES, 0, 2);

  glBindVertexArray(0);
}

void drawQuadLine(Shader *shader, uint32_t textureID, vec2 pos, vec2 size,
                  vec4 color, int lineWidth) {
  vec2 points[4] = {
      {pos[0] - size[0] * 0.5f, pos[1] - size[1] * 0.5},
      {pos[0] + size[0] * 0.5f, pos[1] - size[1] * 0.5},
      {pos[0] + size[0] * 0.5f, pos[1] + size[1] * 0.5},
      {pos[0] - size[0] * 0.5f, pos[1] + size[1] * 0.5},
  };

  drawLine(shader, textureID, points[0], points[1], color, lineWidth);
  drawLine(shader, textureID, points[1], points[2], color, lineWidth);
  drawLine(shader, textureID, points[2], points[3], color, lineWidth);
  drawLine(shader, textureID, points[3], points[0], color, lineWidth);
}

void drawQuad(Shader *shader, uint32_t textureID, vec3 pos, float rotation,
              vec2 size, vec4 color) {

  bindShader(shader->id);

  mat4x4 model;
  mat4x4_identity(model);

  mat4x4_translate(model, pos[0], pos[1], pos[2]);
  mat4x4_rotate(model, model, 0.0f, 0.0f, 1.0f, rotation);
  mat4x4_scale_aniso(model, model, size[0], size[1], 1);

  setMat4(shader, "model", model);
  setFloat4(shader, "color", color);

  glBindVertexArray(_state2D.quadVao);
  glBindTexture(GL_TEXTURE_2D, textureID);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
  glBindVertexArray(0);
}

void drawTriangle(Shader *shader, uint32_t textureID, vec3 pos, float rotation,
                  vec2 size, vec4 color) {

  bindShader(shader->id);

  mat4x4 model;
  mat4x4_identity(model);

  mat4x4_translate(model, pos[0], pos[1], 0);
  mat4x4_rotate(model, model, 0.0f, 0.0f, 1.0f, rotation);
  mat4x4_scale_aniso(model, model, size[0], size[1], 1);

  setMat4(shader, "model", model);
  setFloat4(shader, "color", color);

  glBindVertexArray(_state2D.triangleVao);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}

void drawCircle(Shader *shader, uint32_t textureID, vec3 pos, float radius,
                vec4 color) {

  vec2 size = {2.0f * radius, 2.0f * radius};
  drawQuad(shader, textureID, pos, 0.0f, size, color);
}
