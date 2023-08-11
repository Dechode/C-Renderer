#pragma once

#include "shader.h"
#include "linmath.h"
#include "texture.h"

typedef struct {
  float rotation;
  vec3 position;
  vec2 size;
  vec2 scale;
  Texture texture;
} Sprite;

void initSprite(Sprite *sprite, const char *texturePath, vec3 pos,
                float rotation, vec2 scale);
void drawSprite(Sprite *sprite, Shader *shader);

