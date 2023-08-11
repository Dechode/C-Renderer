#pragma once

#include "glad/glad.h"
#include "linmath.h"

typedef struct {
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

void initCamera(Camera *camera, vec3 position, vec3 up, float yaw, float pitch,
                float moveSpeed, float zoom);
void getViewMatrix(mat4x4 result, Camera *camera);
void updateCameraVectors(Camera *camera);

