#include "MainController.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "../view/View.h"
#include "../model/World.h"
#include "PlayerController.h"


using namespace std;

void runGame(void);

View* view;
World* world;
PlayerController* Controller;

MainController::MainController()
{
	printf("Loading game....\n");
}

MainController::~MainController()
{
	printf("Exiting game.\n");
	delete view;
	delete Controller;
	delete world;
	

	printf("Done!");
	SDL_Delay(3000);
	SDL_Quit();
}

void MainController::start()
{
	printf("Starting game...\n");

	//SDL returns -1 if it failed.
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		printf("Ops! Could not initialize SDL.\n Cause: %s\n", SDL_GetError());
		return;
	}

	world = new World();
	Controller = new PlayerController(world);
	view = new View(1200, 700, "Druid Game");

	if (view->init(world->getMap()) == -1)
	{
		printf("Unable to initialize view. Aborting.\n");
		SDL_Delay(10000);
		return;
	}

	view->Start();

	printf("Game started!\n----------------------------------\n\n");
	runGame();
}

void runGame()
{
	SDL_Event event;
	bool running = true;
	float dTime = 0;
	float cTime = 0;
	float tTime = 0;

	float printCounter = 0;

	while (running)
	{
		
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			Controller->checkInputs(event);
		}

		Controller->update();
		world->Update(dTime);
		view->Update(dTime);

		SDL_Delay(10);

		cTime = (float)SDL_GetTicks()/1000;
		dTime = cTime - tTime;
		tTime = cTime;
		printCounter += dTime;

		if (printCounter > 1)
		{
			printf("FPS: %f\n", 1/dTime);
			printCounter = 0;
		}
	}
}
