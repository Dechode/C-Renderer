#pragma once

#include "math/linmath.h"
#include <stdio.h>

void printVec4(vec4 v) {
  printf("%2.2f, %2.2f, %2.2f, %2.2f\n", v[0], v[1], v[2], v[3]);
}

void printMat4(mat4x4 m) {
  printVec4(m[0]);
  printVec4(m[1]);
  printVec4(m[2]);
  printVec4(m[3]);
  puts("");
}
