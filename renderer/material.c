#include "material.h"
#include "shader.h"
#include "texture.h"

#include <stdio.h>

void initMaterial(Material *material, Shader *shader, Texture *diffTex,
                  Texture *specTex, float shininess) {

  if (shader->id <= 0) {
    printf("Shader not initialized when making material\n");
    return;
  }

  material->shader = shader;

  material->shininess = shininess;
  material->diffuseTexture = diffTex;
  // if (diffTex->textureData){

  // initImageTexture(diffTex, )
  // }
  material->specularTexture = specTex;
}

// Material *createMaterial() {
// }