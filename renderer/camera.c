#include "camera.h"
#include <stdint.h>

static void _initCamera(Camera *camera, vec3 position, vec3 up) {

  vec3_dup(camera->position, position);
  vec3_dup(camera->up, up);
  vec3_dup(camera->globalUp, (vec3){0.0f, 1.0f, 0.0f});
  vec3_dup(camera->front, (vec3){0.0f, 0.0f, -1.0f});

  camera->yaw = 0.0f;
  camera->pitch = 0.0f;

  mat4x4 m;
  mat4x4_identity(m);
  mat4x4_dup(camera->view, m);
}

void initCamera3D(Camera *camera, vec3 position, vec3 up, float vFov,
                  float near, float far, uint32_t windowWidth,
                  uint32_t windowHeight) {

  _initCamera(camera, position, up);
  mat4x4_perspective(camera->projection, vFov,
                     (float)windowWidth / (float)windowHeight, near, far);
  // updateCameraVectors(camera);
  updateCamera(camera);
}

void initCamera2D(Camera *camera, vec3 position, vec3 up, uint32_t windowWidth,
                  uint32_t windowHeight) {

  _initCamera(camera, position, up);
  mat4x4_ortho(camera->projection, 0.0f, (float)windowWidth, 0.0f,
               (float)windowHeight, -100.0f, 100.0f);
  // updateCameraVectors(camera);
  updateCamera(camera);
}

void updateCameraVectors(Camera *camera) {

  vec3 newFront, newRight, newUp;

  newFront[0] = cosf(camera->yaw) * cosf(camera->pitch);
  newFront[1] = sin(camera->pitch);
  newFront[2] = sin(camera->yaw) * cosf(camera->pitch);
  if (vec3_len(newFront) > 1.0f) {
    vec3_norm(camera->front, newFront);
  }

  vec3_mul_cross(newRight, camera->front, camera->globalUp);
  if (vec3_len(newRight) > 1.0f) {
    vec3_norm(camera->right, newRight);
  }

  vec3_mul_cross(newUp, camera->right, camera->front);
  if (vec3_len(newUp) > 1.0f) {
    vec3_norm(camera->up, newUp);
  }
}

void updateCamera(Camera *camera) {
  updateCameraVectors(camera);
  vec3 tmp = {0};
  vec3_add(tmp, camera->position, camera->front);
  mat4x4_look_at(camera->view, camera->position, tmp, camera->up);
}
