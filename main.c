#include "stdio.h"
#include "renderer.c"

static int shouldQuit = 0;

void gameLoop(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
			case SDL_QUIT:
				shouldQuit = 1;
				break;
			
			default:
				break;
		}
    }
}

int main(int argc, char* argv[])
{
	SDL_Window* window;
	window = renderInitWindow(800, 600, "Joukahaisia");

	while (!shouldQuit)
	{
		gameLoop();
	}
}


