#pragma once
#include "stdint.h"
#include "SDL2/SDL.h"
#include "glad/glad.h"

typedef struct renderState {
    uint32_t quadVao;
    uint32_t quadVbo;
    uint32_t quadEbo;

    uint32_t lineVao;
    uint32_t lineVbo;
    
    uint32_t shaderDefault;
    uint32_t textureColor;
    //mat4x4 projection;

} RenderState;


SDL_Window *renderInitWindow(uint32_t width, uint32_t height, char* title)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not init SDL!: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow(title , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    if (!window) {
        printf("Could not init window!: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        printf("Could not init GL!: %s\n", SDL_GetError());
        exit(1);
    }

    puts("OpenGL Loaded!");
    printf("Vendor = %s\n", glGetString(GL_VENDOR));
    printf("Renderer = %s\n", glGetString(GL_RENDERER));
    printf("Version = %s\n", glGetString(GL_VERSION));

    return window;
}
