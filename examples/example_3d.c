#include "../colors.h"
#include "../renderer/3d/renderer_3d.h"
#include "../renderer/renderer.h"
#include "../window.h"
#include "stdio.h"
#include <SDL2/SDL_events.h>
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
  initRenderer3D(state, 1.0f, 0.1f, 100.0f);

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
  float rot = 0.0f;

  setWindowTitle(&window, "3D Cube Example");

  while (!shouldQuit) {
    SDL_Event event;
    handleEvents(&event);

    rot += 0.02;

    renderBegin();

    drawCube((vec3){0.0f, 0.0f, -10.0f}, (vec3){0.0f, 1.0f, 0.0f}, 
            rot, (vec3){3.0f, 4.0f, 5.0f}, COLOR_BLUE);

    renderEnd(window.sdlWindow);
  }
}

void cleanUp(void) { SDL_DestroyWindow(window.sdlWindow); }

int main(int argc, char *argv[]) {
  init();
  run();
  cleanUp();
}
