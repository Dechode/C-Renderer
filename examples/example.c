#include "stdio.h"
#include "../renderer.h"

static int shouldQuit = 0;

typedef struct 
{
	float x,y;
	vec2 size;
	vec4 color;
} Quad;

Quad testQuad;

void gameLoop(void)
{
	testQuad.x = width * 0.5;
	testQuad.y = height * 0.5;
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

	renderQuad((vec2){testQuad.x, testQuad.y}, (vec2){60,60}, (vec4){1.0, 1.0, 0.5, 1.0});
	renderQuad((vec2){width * 0.1, height * 0.9}, (vec2){60,60}, (vec4){1.0, 1.0, 0.5, 1.0});
	renderTriangle((vec2){width * 0.7, height * 0.6}, (vec2){60,60}, (vec4){1.0, 1.0, 0.4, 1.0});

	renderEnd();
}

int main(int argc, char* argv[])
{
	SDL_Window* window;
	initRenderer(800, 600, "Example");

	while (!shouldQuit)
	{
		gameLoop();
	}
}


