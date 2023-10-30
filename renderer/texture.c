#include "texture.h"
#include "../glad/glad.h"
#include <stdint.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

void initImageTexture(Texture *texture, const char *path) {
  texture->textureData = NULL;
  texture->width = 0;
  texture->height = 0;
  texture->numChannels = 0;

  stbi_set_flip_vertically_on_load(1);
  texture->textureData = stbi_load(path, &texture->width, &texture->height,
                                   &texture->numChannels, 0);
  strcpy(texture->path, path);

  if (!texture->textureData) {
    printf("ERROR: Could not load image at path: %s\n", path);
    return;
  }

  glGenTextures(1, &texture->id);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->width, texture->height, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, texture->textureData);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  stbi_image_free(texture->textureData);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void initColorTexture(Texture *texture, vec4 color) {
  texture->textureData = NULL;
  texture->width = 1;
  texture->height = 1;
  texture->numChannels = 0;
  strcpy(texture->path, "");

  glGenTextures(1, &texture->id);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  uint8_t solidColor[4] = {(uint8_t)(255.0f * color[0]), (uint8_t)(color[1] * 255.0f),
                           (uint8_t)(color[2] * 255.0f), (uint8_t)(color[3] * 255.0f)};
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               solidColor);
  glBindTexture(GL_TEXTURE_2D, 0);
}
