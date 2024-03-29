#include "../colors.h"
#include "../obj_loader.h"
#include "../renderer/3d/mesh.h"
#include "../renderer/3d/renderer_3d.h"
#include "../renderer/renderer.h"
#include "../renderer/texture.h"
#include "../window.h"
#include "stdio.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <stddef.h>
#include <stdint.h>

#define WIDTH 1280
#define HEIGHT 720

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
  RenderState3D *_state3D = getRenderState3D();

  Texture woodTexture, colorTexture, specularTexture;
  initImageTexture(&woodTexture, "textures/brick.png");
  initColorTexture(&colorTexture, COLOR_WHITE);
  initColorTexture(&specularTexture, COLOR_WHITE);

  Material material, material2 = {0};
  initMaterial(&material, &_state3D->lightingShader, &woodTexture,
  &specularTexture, 0.4f);
  initMaterial(&material2, &_state3D->lightingShader, &colorTexture,
               &specularTexture, 0.4f);

  Mesh *objMesh = loadObj("obj/torus.obj");
  initMesh(objMesh, objMesh->vertices, objMesh->indices, objMesh->vertexCount,
           objMesh->indexCount);
  
  setWindowTitle(&window, "3D Example");

  while (!shouldQuit) {
    SDL_Event event;
    handleEvents(&event);

    rot += 0.01;

    renderBegin();

    updateCamera(&state->camera);

    drawMesh(objMesh, &material, (vec3){0.0f, 0.0f, -6.0f}, (vec3){1.0f,
    1.0f, 0.0f}, rot);
    drawCube(&material, (vec3){5.5f, 0.0f, -15.0f}, (vec3){0.0f, 0.0f, 1.0f}, rot, (vec3){2.0f, 2.0f, 2.0f});

    renderEnd(window.sdlWindow);
  }
}

void clean(void) {
  // Clean everything here
  SDL_DestroyWindow(window.sdlWindow);
}

int main(int argc, char *argv[]) {
  init();
  run();
  clean();
  return 0;
}
