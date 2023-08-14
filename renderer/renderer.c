#include "renderer.h"
#include "camera.h"
#include "shader.h"
#include "texture.h"

static RenderState renderState = {0};

void initRenderer(void) {

  renderState.defaultShader =
      createShader("shaders/default.frag.glsl", "shaders/default.vert.glsl");

  mat4x4 identityMat4;
  mat4x4_identity(identityMat4);

  bindShader(renderState.defaultShader.id);
  setMat4(&renderState.defaultShader, "projection", renderState.camera.projection);
  setMat4(&renderState.defaultShader, "view", identityMat4);

  renderState.circleShader =
      createShader("shaders/circle.frag.glsl", "shaders/circle.vert.glsl");

  bindShader(renderState.circleShader.id);
  setMat4(&renderState.circleShader, "projection", renderState.camera.projection);

  initColorTexture(&renderState.colorTexture);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // glEnable(GL_DEPTH_TEST);

}

void renderBegin(void) {
  glClearColor(0.08, 0.1, 0.1, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
}

void renderEnd(SDL_Window *window) { SDL_GL_SwapWindow(window); }

RenderState *getRenderState(void) { return &renderState; }
