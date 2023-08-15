#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>

#include "../glad/glad.h"
#include "../math/linmath.h"
#include "../window.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"

typedef struct {
  int windowWidth;
  int windowHeight;

  Shader defaultShader;
  Shader circleShader;

  // uint32_t colorTexture;
  Texture colorTexture;

  Camera camera;
} RenderState;

void initRenderer(void);

void renderBegin(void);
void renderEnd(SDL_Window *window);

RenderState *getRenderState(void);

