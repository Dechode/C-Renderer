#pragma once

#include "../glad/glad.h"
#include "../math/linmath.h"

typedef struct {
  mat4x4 view;
  mat4x4 projection;
  vec3 position;
  vec3 front;
  vec3 up;
  vec3 right;
  vec3 globalUp;

  float yaw;
  float pitch;

  float moveSpeed;
  float mouseSensitivity;
  float zoom;
} Camera;

void initCamera2D(Camera *camera, vec3 position, vec3 up, uint32_t windowWidth,
                  uint32_t windowHeight);
void initCamera3D(Camera *camera, vec3 position, vec3 up, float vFov,
                  float near, float far, uint32_t windowWidth,
                  uint32_t windowHeight);
void getViewMatrix(mat4x4 result, Camera *camera);
void getProjectionMatrix(mat4x4 result, Camera *camera);
void updateCameraVectors(Camera *camera);
void update(Camera *camera);
