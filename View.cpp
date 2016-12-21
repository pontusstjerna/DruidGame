#include "View.h"
#include <stdio.h>

SDL_Window* Window = NULL;
SDL_Surface* MainSurface = NULL;

SDL_Texture* Background = NULL;
SDL_Renderer* Renderer = NULL;

Map* ActiveMap;

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

	for (int i = 0; i < ActiveMap->GetNumberofObjects(); i++)
	{
		char* currTexture = ActiveMap->GetObjects()[i]->GetSpriteSheetPath();
		for (int j = 0; j < ActiveMap->GetNumberofObjects(); j++)
		{
			if (ActiveMap->GetObjects()[j]->GetSpriteSheetPath() == currTexture)
			{
				ActiveMap->GetObjects()[j]->SetSpriteSheet(LoadTexture(currTexture));
			}
		}
	}
}

void View::Update(float dTime)
{
	SDL_RenderClear(Renderer);
	IncrementFrames(dTime);

	DrawBackground(Renderer);
	DrawBlocks(Renderer);
	DrawPlayer(Renderer);

	//Update screen
	SDL_RenderPresent(Renderer);

	//SDL_UpdateWindowSurface(Window);
}

float FrameCounter = 0;
void View::IncrementFrames(float dTime)
{
	FrameCounter += dTime;
	
	if (FrameCounter > STD_UPDATE_INTERVAL)
	{
		Frame = (Frame + 1) % NUMBEROF_FRAMES;
		FrameCounter = 0;
	}
}

void View::DrawBackground(SDL_Renderer* renderer)
{
	float zoom = 0.5f;
	int h = (int)(WINDOW_HEIGHT*zoom);
	SDL_Rect sRect = {2, 300/2 - h/2, (int)(WINDOW_WIDTH*zoom), h};
	SDL_Rect dRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	SDL_RenderCopy(renderer, Background, &sRect, &dRect);
}

void View::DrawBlocks(SDL_Renderer* renderer)
{
	for (int i = 0; i < ActiveMap->GetNumberofBlocks(); i++)
	{
		SDL_Texture* texture;

		//TODO: Check if inside view rect
		if(IsInsideView(ActiveMap->GetBlocks()[i]))
			DrawBlock(ActiveMap->GetBlocks()[i], renderer);
	}
}

void View::DrawBlock(Block* block, SDL_Renderer* renderer)
{
	int y = (int)((block->GetY() - ActiveMap->GetObjects()[0]->GetY())*Scale) + WINDOW_HEIGHT/2;
	int h = block->GetHeight();
	int mh = block->MIN_HEIGHT;

	//Top row
	DrawBlockRow(block, renderer, top, y);
	
	if (h > mh)
	{
		//Middle vertical
		for (int i = mh; i < h - mh; i += mh)
		{
			DrawBlockRow(block, renderer, middle, y + (int)(i*Scale));
		}

		//Bottom
		DrawBlockRow(block, renderer, bottom, y + (int)((h - mh)*Scale));
	}
}

void View::DrawBlockRow(Block* block, SDL_Renderer* renderer, VerticalPos pos, int y)
{

	int x = (int)((block->GetX() - ActiveMap->GetObjects()[0]->GetX())*Scale) + WINDOW_WIDTH/2;
	int w = block->GetWidth();// -player->GetY();
	int h = block->GetHeight();
	int mw = block->MIN_WIDTH;
	int mh = block->MIN_HEIGHT;

	float zoom = 3;

	if (w > 1 * mw)
	{
		//Draw top left
		SDL_Rect sRect = { 0, pos*mh, mw, mh };
		SDL_Rect dRect = { x, y, (int)(mw*zoom), (int)mh*zoom };
		SDL_RenderCopy(renderer, block->GetTexture(), &sRect, &dRect);
	}

	//Middle blocks
	if (w > 2 * mw)
	{
		//Repeat middle texture for every width bigger than 2.
		for (int i = mw; i < w - mw; i += mw)
		{
			SDL_Rect sRect = { mw, pos*mh, mw, mh };
			SDL_Rect dRect = { x + (int)(i*zoom), y, (int)(mw*zoom), (int)mh*zoom };
			SDL_RenderCopy(renderer, block->GetTexture(), &sRect, &dRect);
		}
	}

	//Top right, always paint
	SDL_Rect sRect = { mw * 2, pos*mh, mw, mh };
	SDL_Rect dRect = { x + (int)((w - mw)*zoom), y, (int)(mw*zoom), (int)mh*zoom };
	SDL_RenderCopy(renderer, block->GetTexture(), &sRect, &dRect);
}

void View::DrawPlayer(SDL_Renderer* renderer)
{
	
	AnimatedObject* obj = ActiveMap->GetObjects()[0];

	int x = obj->GetX();
	int y = obj->GetY();
	int w = obj->GetWidth();
	int h = obj->GetHeight();

	//The State*height*2 is for frame index, frame height and 2 for number of directions
	SDL_Rect sRect = { Frame*w, obj->GetState()*h*2 + obj->GetDir()*h , w, h };
	SDL_Rect dRect = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, (int)(w*Scale), (int)(h*Scale) };
	SDL_RenderCopy(renderer, obj->GetSpriteSheet(), &sRect, &dRect);

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
	MainSurface = SDL_GetWindowSurface(Window);

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

bool View::IsInsideView(Block* block)
{
	AnimatedObject* player = ActiveMap->GetObjects()[0];
	int x = (int)((block->GetX() - ActiveMap->GetObjects()[0]->GetX())*Scale) + WINDOW_WIDTH / 2;
	int y = (int)((block->GetY() - ActiveMap->GetObjects()[0]->GetY())*Scale) + WINDOW_HEIGHT / 2;
	int w = (int)(block->GetWidth()*Scale);
	int h = (int)(block->GetHeight()*Scale);
	return x + w > 0 && x < WINDOW_WIDTH && y + h > 0 && y < WINDOW_HEIGHT;
}