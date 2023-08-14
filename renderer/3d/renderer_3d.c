#include "renderer_3d.h"
#include "primitives_3d.h"
#include <stdio.h>
#include <string.h>

static RenderState3D _state3D;
RenderState *_internalState = NULL;

void initCube(void) {

  Vertex *vertices = (Vertex *)malloc(36 * sizeof(Vertex));
  memcpy(vertices, &cubeVertices, 36 * sizeof(Vertex));

  glGenVertexArrays(1, &_state3D.cubeVao);
  glGenBuffers(1, &_state3D.cubeVbo);
  glBindVertexArray(_state3D.cubeVao);
  glBindBuffer(GL_ARRAY_BUFFER, _state3D.cubeVbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  initColorTexture(&_internalState->colorTexture);
}

void initRenderer3D(RenderState *state, float vFov, float near, float far) {
  _internalState = state;
  _state3D.near = near;
  _state3D.far = far;
  _state3D.lightingShader = createShader("shaders/lighting_3d.frag.glsl",
                                         "shaders/lighting_3d.vert.glsl");
  initCamera3D(&_internalState->camera, (vec3){0.0f, 0.0f, 0.0f},
               (vec3){0.0f, 1.0f, 0.0f}, vFov, near, far,
               _internalState->windowWidth, _internalState->windowHeight);
  initCube();
  puts("3D Renderer initialized");
}

void draw(Shader *shader, uint32_t vao, uint32_t indexCount, mat4x4 transform) {
  bindShader(shader->id);
  mat4x4 view;
  getViewMatrix(view, &_internalState->camera);
  setMat4(shader, "projection", _internalState->camera.projection);
  setMat4(shader, "view", view);
  setMat4(shader, "model", transform);
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
}

void drawCube(vec3 position, vec3 rotation, float angle, vec3 size,
              vec4 color) {

  bindShader(_state3D.lightingShader.id);

  mat4x4 model;
  mat4x4_identity(model);
  mat4x4_translate(model, position[0], position[1], position[2]);
  mat4x4_rotate(model, model, rotation[0], rotation[1], rotation[2], angle);
  mat4x4_scale_aniso(model, model, size[0], size[1], size[2]);

  setMat4(&_state3D.lightingShader, "model", model);
  setMat4(&_state3D.lightingShader, "view", _internalState->camera.view);
  setMat4(&_state3D.lightingShader, "projection",
          _internalState->camera.projection);
  setFloat4(&_state3D.lightingShader, "color", color);

  glBindVertexArray(_state3D.cubeVao);
  glBindTexture(GL_TEXTURE_2D, _internalState->colorTexture);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}
