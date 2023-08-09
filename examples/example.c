#include "../renderer.h"
#include "stdio.h"
#include <SDL2/SDL_video.h>

#define WIDTH 800
#define HEIGHT 600

static int shouldQuit = 0;

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

void gameLoop(SDL_Window *window) {
  Sprite sprite;
  initSprite(&sprite, "textures/car16x16.png",
             (vec3){0.5f * WIDTH, 0.5f * HEIGHT, 0.0f}, 0.0f,
             (vec2){10.0, 10.0});

  float triRot = 0.0f;

  while (!shouldQuit) {
    SDL_Event event;
    handleEvents(&event);

    renderBegin();

    sprite.rotation += 0.01f;
    triRot += 0.02f;
    
    drawSprite(&sprite);
    drawTriangle((vec2){WIDTH * 0.7, HEIGHT * 0.6}, triRot, (vec2){60, 60},
                   (vec4){1.0, 1.0, 0.4, 1.0});
    drawCircle((vec3){50.0f, 100.0f, 0.0f}, 40.0f, (vec4){1.0f, 1.0f, 1.0f, 1.0f});

    renderEnd(window);
  }
}

int main(int argc, char *argv[]) {
  SDL_Window *window;
  window = initWindow(800, 600, "Example");
  initRenderer();

  gameLoop(window);

  SDL_DestroyWindow(window);
}
