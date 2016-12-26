#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Map.h"

class GameView
{
	public:
		GameView(int winWidth, int winHeight, Map* map);

		void DrawBackground(SDL_Renderer* renderer, float scale);
		void DrawBlocks(SDL_Renderer* renderer, float scale);
		void DrawPlayer(SDL_Renderer* renderer, float scale);

	private:
		enum VerticalPos { top, middle, bottom };

		Map* ActiveMap;
		int WinWidth = 0;
		int WinHeight = 0;
		int Frame = 0;

		void DrawBlock(Block* block, SDL_Renderer* renderer);
		void DrawBlockRow(Block* block, SDL_Renderer* renderer, VerticalPos pos, int y);
		bool IsInsideView(Block* block);
		void IncrementFrames(float dTime);
};