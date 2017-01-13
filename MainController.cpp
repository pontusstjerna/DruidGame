#include "MainController.h"
#include <SDL.h>
#include <stdio.h>
#include "View.h"
#include "World.h"
#include "PlayerController.h"


using namespace std;

void GameLoop(void);

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
	delete Controller;
	delete world;
	delete view;

	printf("Done!");
	SDL_Delay(1000);
	SDL_Quit();
}

void MainController::Start()
{
	printf("Starting game...\n");

	//SDL returns -1 if it failed.
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		printf("Ops! Could not initialize SDL.\n Cause: %s\n", SDL_GetError());
		return;
	}

	world = new World();
	Controller = new PlayerController(world->GetPlayer());
	view = new View(1200, 700, "Druid Game");

	if (view->InitView() == -1)
	{
		printf("Unable to initialize view. Aborting.\n");
		SDL_Delay(10000);
		return;
	}

	if (view->LoadMap(world->GetMap()) == -1)
	{
		printf("Unable to load map. Aborting.\n");
		SDL_Delay(10000);
		return;
	}

	if (view->LoadPlayer(world->GetPlayer()) == -1)
	{
		printf("Unable to load player. Aborting.\n");
		SDL_Delay(10000);
		return;
	}

	view->Start();

	printf("Game started!\n----------------------------------\n\n");
	GameLoop();
}

void GameLoop()
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
			Controller->UpdateInputs(event);
		}

		Controller->Update();
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