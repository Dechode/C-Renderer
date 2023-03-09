#include "stdio.h"
#include "../renderer.h"

#define WIDTH 800
#define HEIGHT 600

static int shouldQuit = 0;

void handleEvents(SDL_Event* event)
{
	while (SDL_PollEvent(event))
	{
		switch (event->type)
		{
			case SDL_QUIT:
				shouldQuit = 1;
				break;
			
			default:
				break;
		}
    }
}

void gameLoop(SDL_Window* window)
{
	Sprite sprite;
	sprite.width = 60;
	sprite.height = 60;
	sprite.position[0] = 0.0;
	sprite.position[1] = 0.0;

	SDL_Event event;
	handleEvents(&event);
	
	renderBegin();

	renderQuad((vec2){sprite.position[0], sprite.position[1]}, (vec2){60,60}, (vec4){1.0, 1.0, 0.5, 1.0});
	renderQuad((vec2){WIDTH * 0.1, HEIGHT * 0.9}, (vec2){60,60}, (vec4){1.0, 1.0, 0.5, 1.0});
	renderTriangle((vec2){WIDTH * 0.7, HEIGHT * 0.6}, (vec2){60,60}, (vec4){1.0, 1.0, 0.4, 1.0});

	renderEnd(window);
}

int main(int argc, char* argv[])
{
	SDL_Window* window;
	window = initWindow(800, 600, "Example");
	initRenderer();

	while (!shouldQuit)
	{
		gameLoop(window);
	}
}


