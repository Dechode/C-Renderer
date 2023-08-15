#pragma once
#include "../../math/linmath.h"

typedef struct {
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
} DirectionalLight;

void initDirectionalLight(DirectionalLight *light, vec3 direction, vec3 ambient,
                          vec3 diffuse, vec3 specular);
