#include "transform.h"
#include "linmath.h"

Transform2D createTransform2D(vec3 position, float rotation) {
  Transform2D t = {0};
  vec3_dup(t.position, position);
  t.rotation = rotation;
  t.sin = sinf(rotation);
  t.cos = cosf(rotation);
  return t;
}

