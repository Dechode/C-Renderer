#include "sprite.h"
#include "../../colors.h"
// #include "glad/glad.h"
// #include "renderer.h"
#include "renderer_2d.h"

void initSprite(Sprite *sprite, const char *texturePath, vec3 pos,
                float rotation, vec2 scale) {

  initImageTexture(&sprite->texture, texturePath);

  sprite->rotation = rotation;

  sprite->scale[0] = scale[0];
  sprite->scale[1] = scale[1];

  sprite->size[0] = sprite->texture.width * scale[0];
  sprite->size[1] = sprite->texture.height * scale[1];

  sprite->position[0] = pos[0];
  sprite->position[1] = pos[1];
  sprite->position[2] = pos[2];
}

void drawSprite(Sprite *sprite, Shader *shader) {
  drawQuad(shader, sprite->texture.id, sprite->position, sprite->rotation,
           sprite->size, COLOR_WHITE);
}
