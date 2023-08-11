#include "../window.h"
#include "../colors.h"
#include "../mesh.h"
#include "../primitives_3d.h"
#include "../renderer.h"
#include "../renderer_2d.h"
#include "../renderer_3d.h"
#include "../sprite.h"
#include "../window.h"
#include "stdio.h"
#include <SDL2/SDL_video.h>
#include <stddef.h>
#include <stdint.h>

#define WIDTH 800
#define HEIGHT 600

static int shouldQuit = 0;
Window window;
RenderState *state;

void init(void) {
  window = createWindow(WIDTH, HEIGHT, "OpenGL Renderer");
  state = getRenderState();
  SDL_GetWindowSize(window.sdlWindow, &state->windowWidth,
                    &state->windowHeight);
  initRenderer();
  initRenderer2D();
  initRenderer3D(state);

  printf("Window size = (%d x %d)\n", state->windowWidth, state->windowHeight);
}

void handleEvents(SDL_Event *event) {
  while (SDL_PollEvent(event)) {
    switch (event->type) {
    case SDL_QUIT:
      shouldQuit = 1;
      break;

    default:
      break;
    }
  }
}

void run(void) {
  // Sprite sprite;
  // initSprite(&sprite, "textures/car16x16.png", (vec3){200.0f, 100.0f, 0.0f},
             // 0.0f, (vec2){20.0f, 20.0f});

  float rot = 0.0f;
  initCube();

  while (!shouldQuit) {
    SDL_Event event;
    handleEvents(&event);

    renderBegin();

    // vec3 pos = {200.0f, 300.0f, 0.0f};
    // vec2 size = {100.0f, 300.0f};
    rot += 0.02;
    setWindowTitle(&window, "OpenGL Renderer Title");
    drawCube((vec3){0.0f, 0.0f, -10.0f}, rot, (vec3){3.0f, 4.0f, 5.0f},
             COLOR_BLUE);
    // drawQuad(&state->defaultShader, state->colorTexture, pos, 0.0f, size,
             // COLOR_GREEN);
    // drawCircle(&state->circleShader, state->colorTexture, pos, 40.0f,
               // COLOR_RED);
    // drawSprite(&sprite, &state->defaultShader);

    renderEnd(window.sdlWindow);
  }
}

void cleanUp(void) { SDL_DestroyWindow(window.sdlWindow); }

int main(int argc, char *argv[]) {
  init();
  run();
  cleanUp();
}
