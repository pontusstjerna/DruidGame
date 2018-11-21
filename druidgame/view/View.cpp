#include <stdio.h>

#include "View.h"
#include "../util/SDLUtils.h"
#include "TextureHandler.h"

SDL_Window* window = NULL;
SDL_Texture* background = NULL;
SDL_Renderer* renderer = NULL;

AnimatedPlayer* Player;


View::View(unsigned int width, unsigned int height, char* title) :
//This is called initializer list and is requred for const variables
WINDOW_WIDTH(width), WINDOW_HEIGHT(height), WINDOW_TITLE(title) {
	//Bla bla constructor code
	scale = 3;
}

View::View() : View(800, 600, "Druid Game")
{
	//No arguments, use default
}

View::~View()
{
	printf("Destroying window...\n");
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(renderer);

	delete gView;
	delete gui;
    delete textureHandler;
    
	IMG_Quit();
	SDL_Quit();
}

int View::init(Model* model)
{

	if (CreateWindow() == -1)
		return -1;

	if (CreateRenderer() == -1)
		return -1;

    if (SDLUtils::initSDLImage() == -1)
		return -1;
    
    if (LoadMap(model) == -1)
        return -1;
    
    if (LoadPlayer(model->getPlayer()))
        return -1;
    
    if (InitGUI())
        return -1;

	printf("View successfully initialized.\n");
	return 0;
}

int View::InitGUI()
{
	gui = new GUI(Player, activeMap->GetNumberofObjects(), activeMap->GetObjects());

	SDL_Texture* textures[GUI::nTextures];
	for (int i = 0; i < GUI::nTextures; i++)
	{
		textures[i] = textureHandler->getTexture((char*)gui->GUI_TEXTURES[i])->getTexture();
	}
	return gui->LoadGUI(textures, WINDOW_WIDTH, WINDOW_HEIGHT);
}

int View::LoadMap(Model* map)
{
	activeMap = map;
	background = textureHandler->getTexture(map->GetBackground())->getTexture();
	if (background == NULL)
	{
		return -1;
	}

	LoadTextures();

	return 0;
}

int View::LoadPlayer(AnimatedPlayer* player)
{
	Player = player;
    
    // TODO: Simply always use textureHandler for this
	for (int i = 0; i < player->GetNumSpriteSheets(); i++)
	{
		Player->SetSpriteSheet(textureHandler->getTexture(Player->GetSpriteSheetPaths()[i])->getTexture(), i);
	}

	return 0;
}

void View::LoadTextures()
{
	for (int i = 0; i < activeMap->GetNumberofBlocks(); i++)
	{
		char* currTexture = activeMap->GetBlocks()[i]->GetTexturePath();
		for (int j = 0; j < activeMap->GetNumberofBlocks(); j++)
		{
			if (activeMap->GetBlocks()[j]->GetTexturePath() == currTexture)
			{
				activeMap->GetBlocks()[j]->SetTexture(textureHandler->getTexture(currTexture)->getTexture());
			}
		}
	}

	for (int i = 1; i < activeMap->GetNumberofObjects(); i++)
	{
		char* currTexture = activeMap->GetObjects()[i]->GetSpriteSheetPath();
		for (int j = 1; j < activeMap->GetNumberofObjects(); j++)
		{
					
			if (activeMap->GetObjects()[j]->GetSpriteSheetPath() == currTexture)
			{
				activeMap->GetObjects()[j]->SetSpriteSheet(textureHandler->getTexture(currTexture)->getTexture());
			}
		}
	}
}

void View::Start()
{
	gView = new GameView(WINDOW_WIDTH, WINDOW_HEIGHT, activeMap, Player);

	printf("View started.\n");
}

void View::Update(float dTime)
{
	SDL_RenderClear(renderer);
	gView->IncrementFrames(dTime);

	gView->UpdateActiveObjects(scale);
	gView->DrawBackground(renderer, background, scale);
	gView->DrawBlocks(renderer, scale);
	gView->DrawPlayer(renderer, scale);
	gView->DrawAnimatedObjects(renderer, scale);
	gui->Draw(renderer);

	//Update screen
	SDL_RenderPresent(renderer);

	//SDL_UpdateWindowSurface(Window);
}

int View::CreateWindow()
{
	window = SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("Could not create window. \nCause: %s\n", SDL_GetError());
		return -1;
	}

	return 0;
}

int View::CreateSurface()
{

	if (window == NULL)
	{
		printf("Could not create surface. \nCause: %s\n", SDL_GetError());
		return -1;
	}

	return 0;
}

int View::CreateRenderer()
{
	//Using OpenGL
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
		return -1;

	SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
    
    textureHandler = new TextureHandler(renderer);

	return 0;
}
