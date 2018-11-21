#include "View.h"
#include <stdio.h>

SDL_Window* Window = NULL;
SDL_Texture* Background = NULL;
SDL_Renderer* Renderer = NULL;

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
	SDL_DestroyWindow(Window);
	SDL_DestroyTexture(Background);
	SDL_DestroyRenderer(Renderer);

	delete gView;
	delete gui;

	for (int i = 0; i < textures.size(); i++) {
		delete textures.at(i);
	}


	IMG_Quit();
	SDL_Quit();
}

int View::init(Model* model)
{

	if (CreateWindow() == -1)
		return -1;

	if (CreateRenderer() == -1)
		return -1;

	if (InitSDLImage() == -1)
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
		textures[i] = LoadTexture((char*)gui->GUI_TEXTURES[i]);
	}
	return gui->LoadGUI(textures, WINDOW_WIDTH, WINDOW_HEIGHT);
}

int View::LoadMap(Model* map)
{
	activeMap = map;
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
	for (int i = 0; i < activeMap->GetNumberofBlocks(); i++)
	{
		char* currTexture = activeMap->GetBlocks()[i]->GetTexturePath();
		for (int j = 0; j < activeMap->GetNumberofBlocks(); j++)
		{
			if (activeMap->GetBlocks()[j]->GetTexturePath() == currTexture)
			{
				activeMap->GetBlocks()[j]->SetTexture(LoadTexture(currTexture));
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
				activeMap->GetObjects()[j]->SetSpriteSheet(LoadTexture(currTexture));
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
	SDL_RenderClear(Renderer);
	gView->IncrementFrames(dTime);

	gView->UpdateActiveObjects(scale);
	gView->DrawBackground(Renderer, Background, scale);
	gView->DrawBlocks(Renderer, scale);
	gView->DrawPlayer(Renderer, scale);
	gView->DrawAnimatedObjects(Renderer, scale);
	gui->Draw(Renderer);

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
	
	for (int i = 0; i < textures.size(); i++)
	{
		if (strcmp(textures.at(i)->getPath(), path) == 0)
		{
			return textures.at(i)->getTexture();
		}
	}

	SDL_Texture* texture = NULL;

	SDL_Surface* tmpSurface = IMG_Load(path);

	if (tmpSurface == NULL)
		printf("Unable to load image: %s. \nCause: %s\n", path, SDL_GetError());

	texture = SDL_CreateTextureFromSurface(Renderer, tmpSurface);
	if (texture == NULL)
		printf("Unable to load texture. \nCause: %s\n", SDL_GetError());

	//Reallocate
	SDL_FreeSurface(tmpSurface);

	//Add texture to texture list
	textures.push_back(new Texture(texture, path));

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
