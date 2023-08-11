#include "primitives_3d.h"
#include "glad/glad.h"
#include "linmath.h"
#include "mesh.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static uint32_t _cubeVao;
static uint32_t _cubeVbo;
static Shader _cubeShader;
static uint32_t _cubeTexture;

static float cubeVertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

    -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

// static Mesh cube;

void initCube(void) {

  // Vertex *vertices = (Vertex*)malloc(8 * sizeof(Vertex));
  // for (uint32_t i = 0; i < 8; i++) {
  //   for (uint32_t j = 0; j < 3; j++) {
  //     vertices[i].positions[j] = cubeVertexPositions[j];
  //   }
  // }
  // initMeshSolidColor(&cube, vertices, NULL, 8, 0);

  glGenVertexArrays(1, &_cubeVao);
  glGenBuffers(1, &_cubeVbo);
  glBindVertexArray(_cubeVao);
  glBindBuffer(GL_ARRAY_BUFFER, _cubeVbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  initColorTexture(&_cubeTexture);
  _cubeShader = getRenderState()->defaultShader;
}

void drawCube(vec3 position, float rotation, vec3 size, vec4 color) {

  bindShader(_cubeShader.id);

  mat4x4 model, view, projection;

  mat4x4_identity(model);
  mat4x4_identity(view);
  mat4x4_identity(projection);

  mat4x4_translate(view, 0.0f, 0.0f, 0.0f);
  mat4x4_perspective(projection, 0.7f, (float)800 / 600, 0.1f, 100.0f);
  mat4x4_translate(model, position[0], position[1], position[2]);
  mat4x4_rotate(model, model, 0.0f, 0.5f, 1.0f, rotation);
  mat4x4_scale_aniso(model, model, size[0], size[1], size[2]);

  setMat4(&_cubeShader, "model", model);
  setMat4(&_cubeShader, "view", view);
  setMat4(&_cubeShader, "projection", projection);
  setFloat4(&_cubeShader, "color", color);

  glBindVertexArray(_cubeVao);
  glBindTexture(GL_TEXTURE_2D, _cubeTexture);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}

// float *getCubeVertices(void) { return cubeVertices; }
