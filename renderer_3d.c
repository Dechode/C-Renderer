#include "renderer_3d.h"
#include "camera.h"
#include "glad/glad.h"
#include "linmath.h"
#include "renderer.h"
#include "shader.h"
#include <stdio.h>

// static RenderState3D _state3D;
RenderState *_internalState = NULL;

void initRenderer3D(RenderState *state) {
  _internalState = state;
  puts("3D Renderer initialized");
}

void draw3D(Shader *shader, uint32_t vao, uint32_t indexCount, mat4x4 transform) {
  bindShader(shader->id);
  mat4x4 tmpMat4;
  getViewMatrix(tmpMat4, &_internalState->camera);
  setMat4(shader, "projection", _internalState->projection);
  // setMat4(shader, "view", tmpMat4);
  // setMat4(shader, "transform", transform);
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
}

