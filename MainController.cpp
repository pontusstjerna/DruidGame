#include "MainController.h"
#include <SDL.h>
#include <stdio.h>
#include "View.h"


using namespace std;

void GameLoop(void);

View* view;

MainController::MainController()
{
	printf("Loading game....\n");
}

MainController::~MainController()
{
	printf("Exiting game.\n");
	delete view;

	printf("Done!");
	SDL_Delay(2000);
	SDL_Quit();
}

void MainController::Start()
{
	printf("Starting game...\n");

	view = new View(800, 600, "Druid Game");

	if (view->InitView() == -1)
	{
		printf("Unable to initialize view. Aborting.\n");
		SDL_Delay(10000);
		return;
	}

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

		view->Update(0);

		SDL_Delay(10);
	}
}