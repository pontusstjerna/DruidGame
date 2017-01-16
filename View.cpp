#include "View.h"
#include <stdio.h>

SDL_Window* Window = NULL;
SDL_Texture* Background = NULL;
SDL_Renderer* Renderer = NULL;

Map* ActiveMap;
AnimatedPlayer* Player;

//This is called initializer list and is requred for const variables
View::View(unsigned int width, unsigned int height, char* title) : WINDOW_WIDTH(width), WINDOW_HEIGHT(height), WINDOW_TITLE(title)
{
	//Bla bla constructor code
	Scale = 3;
}

View::View() : View(800, 600, "Druid Game")
{
	//No arguments, use default
}

View::~View()
{
	printf("Destroying window...\n");
	SDL_DestroyWindow(Window);
	SDL_DestroyTexture(Background);
	SDL_DestroyRenderer(Renderer);

	delete GView;

	IMG_Quit();
	SDL_Quit();
}

int View::InitView()
{

	if (CreateWindow() == -1)
		return -1;

	if (CreateRenderer() == -1)
		return -1;

	if (InitSDLImage() == -1)
		return -1;

	printf("View successfully initialized.\n");
	return 0;
}

int View::InitGUI()
{
	Gui = new GUI(Player, ActiveMap->GetNumberofObjects(), ActiveMap->GetObjects());
	return Gui->LoadGUI(LoadTexture(Gui->GUI_BACKGROUND));
}

int View::LoadMap(Map* map)
{
	ActiveMap = map;
	Background = LoadTexture(map->GetBackground());
	if (Background == NULL)
	{
		return -1;
	}

	LoadTextures();

	return 0;
}

int View::LoadPlayer(AnimatedPlayer* player)
{
	Player = player;

	for (int i = 0; i < player->GetNumSpriteSheets(); i++)
	{
		Player->SetSpriteSheet(LoadTexture(Player->GetSpriteSheetPaths()[i]), i);
	}

	return 0;
}

void View::LoadTextures()
{
	for (int i = 0; i < ActiveMap->GetNumberofBlocks(); i++)
	{
		char* currTexture = ActiveMap->GetBlocks()[i]->GetTexturePath();
		for (int j = 0; j < ActiveMap->GetNumberofBlocks(); j++)
		{
			if (ActiveMap->GetBlocks()[j]->GetTexturePath() == currTexture)
			{
				ActiveMap->GetBlocks()[j]->SetTexture(LoadTexture(currTexture));
			}
		}
	}

	for (int i = 1; i < ActiveMap->GetNumberofObjects(); i++)
	{
		char* currTexture = ActiveMap->GetObjects()[i]->GetSpriteSheetPath();
		for (int j = 1; j < ActiveMap->GetNumberofObjects(); j++)
		{
					
			if (ActiveMap->GetObjects()[j]->GetSpriteSheetPath() == currTexture)
			{
				ActiveMap->GetObjects()[j]->SetSpriteSheet(LoadTexture(currTexture));
			}
		}
	}
}

void View::Start()
{
	GView = new GameView(WINDOW_WIDTH, WINDOW_HEIGHT, ActiveMap, Player);

	printf("View started.\n");
}

void View::Update(float dTime)
{
	SDL_RenderClear(Renderer);
	GView->IncrementFrames(dTime);

	GView->DrawBackground(Renderer, Background, Scale);
	GView->DrawBlocks(Renderer, Scale);
	GView->DrawPlayer(Renderer, Scale);

	//Update screen
	SDL_RenderPresent(Renderer);

	//SDL_UpdateWindowSurface(Window);
}

int View::CreateWindow()
{
	Window = SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (Window == NULL)
	{
		printf("Could not create window. \nCause: %s\n", SDL_GetError());
		return -1;
	}

	return 0;
}

int View::CreateSurface()
{

	if (Window == NULL)
	{
		printf("Could not create surface. \nCause: %s\n", SDL_GetError());
		return -1;
	}

	return 0;
}

int View::CreateRenderer()
{
	//Using OpenGL
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

	if (Renderer == NULL)
		return -1;

	SDL_SetRenderDrawColor(Renderer, 100, 100, 255, 255);

	return 0;
}

SDL_Texture* View::LoadTexture(char* path)
{
	SDL_Texture* texture = NULL;

	SDL_Surface* tmpSurface = IMG_Load(path);

	if (tmpSurface == NULL)
		printf("Unable to load image: %s. \nCause: %s\n", path, SDL_GetError());

	texture = SDL_CreateTextureFromSurface(Renderer, tmpSurface);
	if (texture == NULL)
		printf("Unable to load texture. \nCause: %s\n", SDL_GetError());

	//Reallocate
	SDL_FreeSurface(tmpSurface);

	return texture;
}

int View::InitSDLImage()
{
	int imgFlags = IMG_INIT_PNG;

	if ((IMG_Init(imgFlags) & imgFlags) == 0)
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return -1;
	}

	return 0;
}                               