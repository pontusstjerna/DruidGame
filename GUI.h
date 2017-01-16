#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "AnimatedPlayer.h"
#include "AnimatedObject.h"

class GUI
{
	public:
		char* GUI_BACKGROUND = "data/gui/GUI_background.png";

		GUI(AnimatedPlayer* player, int nObjects, AnimatedObject**);
		~GUI();

		int LoadGUI(SDL_Texture* background, int win_width, int win_height);

		void Draw(SDL_Renderer* renderer);

	private:
		const int BG_WIDTH = 240;
		const int BG_HEIGHT = 180;

		int WinWidth, WinHeight;

		AnimatedPlayer* Player;
		AnimatedObject** Objects;

		SDL_Texture* Background = NULL;

		int NumObjects = 0;
		bool ShowFps = false;

		void DrawBackground(SDL_Renderer* renderer);
		void DrawHealth(SDL_Renderer* renderer);
		void DrawStamina(SDL_Renderer* renderer);
		void DrawXP(SDL_Renderer* renderer);
		void DrawLevel(SDL_Renderer* renderer);
		void DrawHealthBars(SDL_Renderer* renderer);
		void DrawHealthBar(SDL_Renderer* renderer, AnimatedObject* obj);
		
};