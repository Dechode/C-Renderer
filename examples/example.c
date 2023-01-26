#include "stdio.h"
#include "../renderer.c"

static int shouldQuit = 0;

typedef struct 
{
//	vec2 pos;
	float x,y;
	vec2 size;
	vec4 color;
} Quad;

Quad testQuad;

void gameLoop(void)
{
	// Poll events 
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				shouldQuit = 1;
				break;
			
			default:
				break;
		}
    }
	
	renderBegin();

	renderQuad((vec2){0,0}, (vec2){60,60}, (vec4){1.0, 1.0, 0.5, 1.0});	
	renderEnd();
}

int main(int argc, char* argv[])
{
	SDL_Window* window;
	SCR_RendererInit(800, 600, "Example");

//	testQuad.pos = (vec2){0.0, 0.0};

	while (!shouldQuit)
	{
		gameLoop();
	}
}


