#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "AnimatedPlayer.h"
#include "AnimatedObject.h"

class GUI
{
	public:
		static const int nTextures = 3;
		const char* GUI_TEXTURES[nTextures] { 
			"data/gui/GUI_background.png",
			"data/gui/GUI_healthbar.png",
			"data/gui/GUI_stabar.png"
		};
		static const enum Textures {BACKGROUND, HEALTH_BAR, STA_BAR};

		GUI(AnimatedPlayer* player, int nObjects, AnimatedObject**);
		~GUI();

		int LoadGUI(SDL_Texture** textures, int win_width, int win_height);

		void Draw(SDL_Renderer* renderer);

	private:
		const int BG_WIDTH = 240;
		const int BG_HEIGHT = 180;
		const int PLAYER_BAR_WIDTH = 49;
		const int PLAYER_BAR_HEIGHT = 6;

		int WinWidth, WinHeight;

		AnimatedPlayer* Player;
		AnimatedObject** Objects;

		SDL_Texture** Textures = NULL;

		int NumObjects = 0;
		bool ShowFps = false;

		void DrawBackground(SDL_Renderer* renderer);
		void DrawHealth(SDL_Renderer* renderer);
		void DrawStamina(SDL_Renderer* renderer);
		void DrawXP(SDL_Renderer* renderer);
		void DrawLevel(SDL_Renderer* renderer);
		void DrawHealthBars(SDL_Renderer* renderer);
		void DrawHealthBar(SDL_Renderer* renderer, AnimatedObject* obj);
		float GetScaleX();
		float GetScaleY();
		
};