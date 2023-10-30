#pragma once

#include "linmath.h"

typedef struct {
  mat4x4 mat;
  vec3 position;
  float rotation;
  float sin;
  float cos;
} Transform2D;

Transform2D createTransform2D(vec3 position, float rotation);

