#include "lighting.h"

void initDirectionalLight(DirectionalLight *light, vec3 direction, vec3 ambient,
                          vec3 diffuse, vec3 specular) {

  vec3_dup(light->direction, direction);
  vec3_dup(light->diffuse, diffuse);
  vec3_dup(light->ambient, ambient);
  vec3_dup(light->specular, specular);
}
