#include "renderer_3d.h"
#include "../../colors.h"
#include "lighting.h"
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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  initColorTexture(&_internalState->colorTexture, COLOR_BLACK);
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

  vec3 direction = {0.0f, -1.0f, 0.0f};
  vec3 ambient = {0.1f, 0.1f, 0.1f};
  vec3 diffuse = {0.8f, 0.8f, 0.8f};
  vec3 specular = {0.1f, 0.1f, 0.1f};

  initDirectionalLight(&_state3D.sun, direction, ambient, diffuse, specular);
  initCube();

  puts("3D Renderer initialized");
}

void drawElements(Material *material, vec3 position, vec3 rotation, float angle,
                  uint32_t vao, uint32_t indexCount) {

  bindShader(material->shader->id);
  mat4x4 model;
  mat4x4_identity(model);
  mat4x4_translate(model, position[0], position[1], position[2]);
  mat4x4_rotate(model, model, rotation[0], rotation[1], rotation[2], angle);

  setInt(material->shader, "material.diffuse", 0);
  setInt(material->shader, "material.specular", 1);
  setFloat3(material->shader, "viewPos", _internalState->camera.position);
  setFloat(material->shader, "material.shininess", material->shininess);

  setMat4(material->shader, "model", model);
  setMat4(material->shader, "view", _internalState->camera.view);
  setMat4(material->shader, "projection", _internalState->camera.projection);

  setFloat3(material->shader, "directionalLight.direction",
            _state3D.sun.direction);
  setFloat3(material->shader, "directionalLight.diffuse", _state3D.sun.diffuse);
  setFloat3(material->shader, "directionalLight.ambient", _state3D.sun.ambient);
  setFloat3(material->shader, "directionalLight.specular",
            _state3D.sun.specular);

  glBindVertexArray(vao);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, material->diffuseTexture->id);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, material->specularTexture->id);
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
  glBindVertexArray(0);
}

void drawArray(Material *material, vec3 position, vec3 rotation, float angle,
                  uint32_t vao, uint32_t vertexCount) {

  bindShader(material->shader->id);
  mat4x4 model;
  mat4x4_identity(model);
  mat4x4_translate(model, position[0], position[1], position[2]);
  mat4x4_rotate(model, model, rotation[0], rotation[1], rotation[2], angle);

  setInt(material->shader, "material.diffuse", 0);
  setInt(material->shader, "material.specular", 1);
  setFloat3(material->shader, "viewPos", _internalState->camera.position);
  setFloat(material->shader, "material.shininess", material->shininess);

  setMat4(material->shader, "model", model);
  setMat4(material->shader, "view", _internalState->camera.view);
  setMat4(material->shader, "projection", _internalState->camera.projection);

  setFloat3(material->shader, "directionalLight.direction",
            _state3D.sun.direction);
  setFloat3(material->shader, "directionalLight.diffuse", _state3D.sun.diffuse);
  setFloat3(material->shader, "directionalLight.ambient", _state3D.sun.ambient);
  setFloat3(material->shader, "directionalLight.specular",
            _state3D.sun.specular);

  glBindVertexArray(vao);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, material->diffuseTexture->id);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, material->specularTexture->id);
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
  glBindVertexArray(0);
}
void drawCube(Material *material, vec3 position, vec3 rotation, float angle,
              vec3 size) {

  bindShader(material->shader->id);

  mat4x4 model;
  mat4x4_identity(model);
  mat4x4_translate(model, position[0], position[1], position[2]);
  mat4x4_rotate(model, model, rotation[0], rotation[1], rotation[2], angle);
  mat4x4_scale_aniso(model, model, size[0], size[1], size[2]);

  setInt(material->shader, "material.diffuse", 0);
  setInt(material->shader, "material.specular", 1);
  setFloat3(material->shader, "viewPos", _internalState->camera.position);
  setFloat(material->shader, "material.shininess", material->shininess);

  setMat4(material->shader, "model", model);
  setMat4(material->shader, "view", _internalState->camera.view);
  setMat4(material->shader, "projection", _internalState->camera.projection);

  setFloat3(material->shader, "directionalLight.direction",
            _state3D.sun.direction);
  setFloat3(material->shader, "directionalLight.diffuse", _state3D.sun.diffuse);
  setFloat3(material->shader, "directionalLight.ambient", _state3D.sun.ambient);
  setFloat3(material->shader, "directionalLight.specular",
            _state3D.sun.specular);

  glBindVertexArray(_state3D.cubeVao);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, material->diffuseTexture->id);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, material->specularTexture->id);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}

RenderState3D *getRenderState3D(void) { return &_state3D; }
