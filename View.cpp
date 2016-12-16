#include "View.h"
#include <stdio.h>

int CreateWindow();
int CreateSurface();
int CreateRenderer();
SDL_Texture* LoadTexture(char*);


SDL_Window* Window = NULL;
SDL_Surface* MainSurface = NULL;

SDL_Texture* Background = NULL;
SDL_Texture* Foreground = NULL;
SDL_Renderer* Renderer = NULL;

//This is called initializer list and is requred for const variables
View::View(unsigned int width, unsigned int height, char* title) : WINDOW_WIDTH(width), WINDOW_HEIGHT(height), WINDOW_TITLE(title)
{
	//Bla bla constructor code
}

View::View() : View(800, 600, "Rabbit's Laughter")
{
	//No arguments, use default
}

View::~View()
{
	printf("Destroying window...\n");
	SDL_DestroyWindow(Window);
	SDL_DestroyTexture(Background);
	SDL_DestroyRenderer(Renderer);

	SDL_Quit();
}

int View::InitView()
{
	//SDL returns -1 if it failed.
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("Ops! Could not initialize SDL.\n Cause: %s\n", SDL_GetError());
		return -1;
	}

	if (CreateWindow() == -1)
		return -1;

	if (CreateSurface() == -1)
		return -1;

	return 0;
}

void View::Update(int fps)
{
	SDL_FillRect(MainSurface, NULL, SDL_MapRGB((*MainSurface).format, 100, 10, 200));

	SDL_UpdateWindowSurface(Window);
}

int View::CreateWindow()
{
	View = SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (View == NULL)
	{
		printf("Could not create window. \nCause: %s\n", SDL_GetError());
		return -1;
	}

	return 0;
}

int View::CreateSurface()
{
	mainSurface = SDL_GetWindowSurface(View);

	if (View == NULL)
	{
		printf("Could not create surface. \nCause: %s\n", SDL_GetError());
		return -1;
	}

	return 0;
}

int View::CreateRenderer()
{
	//Using OpenGL
	renderer = SDL_CreateRenderer(View, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
		return -1;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

}

SDL_Texture* View::LoadTexture(char* path)
{
	SDL_Texture* texture = NULL;

	SDL_Surface* tmpSurface = SDL_LoadBMP(path);

	if (tmpSurface == NULL)
		printf("Unable to load image: %s. \nCause: %s\n", path, SDL_GetError());

	texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	if (texture == NULL)
		printf("Unable to load texture. \nCause: %s\n", SDL_GetError());

	//Reallocate
	SDL_FreeSurface(tmpSurface);

	return texture;
}