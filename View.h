#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Map.h"
#include "AnimatedPlayer.h"

class View
{
	public:
		const int NUMBEROF_FRAMES = 8;
		const float STD_UPDATE_INTERVAL = 0.05f;

		View();
		View(unsigned int, unsigned int, char*);
		~View();

		int InitView();
		int LoadMap(Map* map);
		int LoadPlayer(AnimatedPlayer* player);
		void Update(float);

	private:
		enum VerticalPos {top, middle, bottom};
		
		int Frame = 0;

		int CreateWindow();
		int CreateSurface();
		int CreateRenderer();
		SDL_Texture* LoadTexture(char*);
		int InitSDLImage();
		void LoadTextures();
		void IncrementFrames(float dTime);

		void DrawBackground(SDL_Renderer* renderer);
		void DrawBlocks(SDL_Renderer* renderer);
		void DrawBlock(Block* block, SDL_Renderer* renderer);
		void DrawBlockRow(Block* block, SDL_Renderer* renderer, VerticalPos pos, int y);
		void DrawPlayer(SDL_Renderer* renderer);

		bool IsInsideView(Block* block);

		const int WINDOW_WIDTH;
		const int WINDOW_HEIGHT;
		char* WINDOW_TITLE;

		float Scale;

};
