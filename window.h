#pragma once

#include "glad/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

typedef struct {
  int width;
  int height;
  const char *title;
  SDL_Window* sdlWindow;
  SDL_GLContext glContext;
} Window;

Window createWindow(int width, int height, const char *title);
void setWindowTitle(Window *window, const char *title);
