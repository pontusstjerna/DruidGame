#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Map.h"
#include "AnimatedPlayer.h"

class GameView
{
	public:
		const int NUMBEROF_FRAMES = 8;
		const float STD_UPDATE_INTERVAL = 0.05f;

		GameView(int winWidth, int winHeight, Map* map, AnimatedPlayer* player);

		void IncrementFrames(float dTime);
		void DrawBackground(SDL_Renderer* renderer, SDL_Texture* background, float scale);
		void DrawBlocks(SDL_Renderer* renderer, float scale);
		void DrawPlayer(SDL_Renderer* renderer, float scale);

	private:
		enum VerticalPos { top, middle, bottom };

		Map* ActiveMap;
		AnimatedPlayer* Player;

		int WinWidth = 0;
		int WinHeight = 0;
		int Frame = 0;

		void DrawBlock(Block* block, SDL_Renderer* renderer, float scale);
		void DrawBlockRow(Block* block, SDL_Renderer* renderer, VerticalPos pos, int x, int y, float scale);
		bool IsInsideView(Block* block, float );
};