#include "MainController.h"
#include <SDL.h>
#include <stdio.h>


using namespace std;

void GameLoop(void);

MainController::MainController()
{
	printf("Loading game....\n");
}

void MainController::Start()
{
	printf("Starting game...\n");

	printf("Game started!\n----------------------------------\n\n");
	GameLoop();
}

void GameLoop()
{
	SDL_Event event;
	bool running = true;

	while (running)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}


		SDL_Delay(10);
	}
}