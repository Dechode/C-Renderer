#include "window.h"
#include "glad/glad.h"
#include <SDL2/SDL_video.h>

Window createWindow(int width, int height, const char *title) {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Could not init SDL video!: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  Window window = {0};
  window.title = title;
  window.sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_OPENGL);

  if (!window.sdlWindow) {
    printf("Could not init window!: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  window.width = width;
  window.height= height;

  window.glContext = SDL_GL_CreateContext(window.sdlWindow);

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    printf("Could not init Open GL!: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  puts("\nOpenGL Loaded!");
  printf("Vendor = %s\n", glGetString(GL_VENDOR));
  printf("Renderer = %s\n", glGetString(GL_RENDERER));
  printf("Version = %s\n\n", glGetString(GL_VERSION));

  return window;
}

void setWindowTitle(Window *window, const char *title) {
  window->title = title;
  SDL_SetWindowTitle(window->sdlWindow, title);
}
