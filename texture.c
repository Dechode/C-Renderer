#include "texture.h"
#include "glad/glad.h"
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(texture->textureData);
}

void initColorTexture(uint32_t *textureID) {

  glGenTextures(1, textureID);
  glBindTexture(GL_TEXTURE_2D, *textureID);

  uint8_t solidWhite[4] = {255, 255, 255, 255};
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               solidWhite);
  glBindTexture(GL_TEXTURE_2D, 0);
}
