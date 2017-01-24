#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Model.h"
#include "AnimatedPlayer.h"

class GameView
{
	public:
		const int NUMBEROF_FRAMES = 8;
		const float STD_UPDATE_INTERVAL = 0.05f;

		GameView(int winWidth, int winHeight, Model* map, AnimatedPlayer* player);

		void IncrementFrames(float dTime);
		void DrawBackground(SDL_Renderer* renderer, SDL_Texture* background, float scale);
		void DrawBlocks(SDL_Renderer* renderer, float scale);
		void DrawPlayer(SDL_Renderer* renderer, float scale);
		void DrawAnimatedObjects(SDL_Renderer* renderer, float scale);

	private:
		enum VerticalPos { top, middle, bottom };

		Model* activeMap;
		AnimatedPlayer* player;

		int winWidth = 0;
		int winHeight = 0;
		int frame = 0;

		void DrawBlock(Block* block, SDL_Renderer* renderer, float scale);
		void DrawBlockRow(Block* block, SDL_Renderer* renderer, VerticalPos pos, int x, int y, float scale);
		void DrawAnimatedObject(AnimatedObject* object, SDL_Renderer* renderer, float scale);
		bool IsInsideView(Block* block, float );
		bool IsInsideView(SDL_Rect rect, float scale);
};