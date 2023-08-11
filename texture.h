#pragma once

#include "max_values.h"
#include <stdint.h>

typedef enum {
  IMAGE,
  COLOR,
} TextureType;

typedef struct {
  unsigned char *textureData;
  char path[MAX_PATH_CHARS];
  uint32_t id;
  int width;
  int height;
  int numChannels;
  TextureType type;
} Texture;

void initImageTexture(Texture *texture, const char *path);
void initColorTexture(uint32_t *textureID);

