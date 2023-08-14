#include "camera.h"

void initCamera(Camera *camera, vec3 position, vec3 up, float yaw, float pitch,
                float moveSpeed, float zoom) {

  vec3_dup(camera->position, position);
  vec3_dup(camera->up, up);
  vec3_dup(camera->globalUp, up);
  vec3_dup(camera->front, (vec3){0.0f, 0.0f, -1.0f});

  camera->yaw = yaw;
  camera->pitch = pitch;
  camera->moveSpeed = moveSpeed;
  camera->mouseSensitivity = 2.0;
  camera->zoom = zoom;

  updateCameraVectors(camera);
}

void updateCameraVectors(Camera *camera) {

  vec3 newFront, newRight, newUp;

  newFront[0] = cosf(camera->yaw) * cosf(camera->pitch);
  newFront[1] = sin(camera->pitch);
  newFront[2] = sin(camera->yaw) * cosf(camera->pitch);
  if (vec3_len(newFront) > 1.0) {
    vec3_norm(camera->front, newFront);
  }
  
  vec3_mul_cross(newRight, camera->front, camera->globalUp);
  if (vec3_len(newRight) > 1.0) {
    vec3_norm(camera->right, newRight);
  }
  
  vec3_mul_cross(newUp, camera->right, camera->front);
  if (vec3_len(newUp) > 1.0) {
    vec3_norm(camera->up, newUp);
  }
}

void getViewMatrix(mat4x4 result, Camera *camera) {
  vec3 tmp;
  vec3_add(tmp, camera->position, camera->front);
  mat4x4_look_at(result, camera->position, tmp, camera->up);
}
