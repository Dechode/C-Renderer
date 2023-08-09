#pragma once

#include "SDL2/SDL.h"
#include "glad/glad.h"
#include "io.h"
#include "linmath.h"
#include "stdint.h"
#include "stdlib.h"
#include <stdint.h>
#include <sys/types.h>

typedef struct {
  uint32_t quadVao;
  uint32_t quadVbo;
  uint32_t quadEbo;

  uint32_t lineVao;
  uint32_t lineVbo;

  uint32_t triangleVao;
  uint32_t triangleVbo;

  uint32_t windowWidth;
  uint32_t windowHeight;

  uint32_t defaultShader;
  uint32_t defaultTexture;

  mat4x4 projection;

} RenderState2D;

typedef struct {
  uint32_t texture;
  unsigned char *textureData;
  int width;
  int height;
  int numChannels;
} ImageTexture;

typedef struct {
  float rotation;
  vec3 position;
  vec2 size;
  vec2 scale;
  ImageTexture texture;
} Sprite;

uint32_t createShader(const char *pathFrag, const char *pathVert);

SDL_Window *initWindow(uint32_t width, uint32_t height, const char *title);
void initRenderer(void);

void initShaders(RenderState2D *state);
void initColorTexture(uint32_t *texture);
void initSprite(Sprite *sprite, const char *texturePath, vec3 pos,
                float rotation, vec2 scale);
void initImageTexture(ImageTexture *texture, const char *path);

void initTriangle(uint32_t *vao, uint32_t *vbo);
void initQuad(uint32_t *vao, uint32_t *vbo, uint32_t *ebo);
void initLine(uint32_t *vao, uint32_t *vbo);

void renderBegin(void);
void renderEnd(SDL_Window *window);

void renderQuad(int32_t texture, int32_t shader, vec3 pos, float rotation,
                vec2 size, vec4 color);
void renderTriangle(vec2 pos, vec2 size, vec4 color);
void renderLineSegment(vec2 start, vec2 end, vec4 color, int lineWidth);
void renderQuadLine(vec2 pos, vec2 size, vec4 color, int lineWidth);

void drawSprite(Sprite *sprite);
