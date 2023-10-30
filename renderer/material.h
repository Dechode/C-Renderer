#pragma once

#include "shader.h"
#include "texture.h"

typedef struct {
  Shader *shader;
  Texture *diffuseTexture;
  Texture *specularTexture;
  float shininess;
} Material;

void initMaterial(Material *material, Shader *shader, Texture *diffTex,
                  Texture *specTex, float shininess);
// void initMaterial(Material *material, Texture *diffTex, Texture *specTex,
