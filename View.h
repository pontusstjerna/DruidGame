#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Map.h"

class View
{
	public:
		View();
		View(unsigned int, unsigned int, char*);
		~View();

		int InitView();
		int LoadMap(Map* map);
		void Update(int);

	private:
		enum VerticalPos {top, middle, bottom};

		int CreateWindow();
		int CreateSurface();
		int CreateRenderer();
		SDL_Texture* LoadTexture(char*);
		int InitSDLImage();
		void LoadTextures();

		void DrawBackground(SDL_Renderer* renderer);
		void DrawBlocks(SDL_Renderer* renderer);
		void DrawBlock(Block* block, SDL_Renderer* renderer);
		void DrawBlockRow(Block* block, SDL_Renderer* renderer, VerticalPos pos, int y);
		void DrawAnimatedObjects(SDL_Renderer* renderer);

		const int WINDOW_WIDTH;
		const int WINDOW_HEIGHT;
		char* WINDOW_TITLE;

		float Scale;

};
