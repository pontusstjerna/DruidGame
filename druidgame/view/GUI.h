#pragma once
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "AnimatedPlayer.h"
#include "../model/GameObject.h"

class GUI
{
	public:
		static const int nTextures = 3;
		const char* GUI_TEXTURES[nTextures] { 
			"GUI_background",
			"GUI_healthbar",
			"GUI_stabar"
		};
		static const enum Textures {BACKGROUND, HEALTH_BAR, STA_BAR};

		GUI(AnimatedPlayer* player, int nObjects, GameObject**);
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
		GameObject** Objects;

		SDL_Texture** Textures = NULL;

		int NumObjects = 0;
		bool ShowFps = false;

		void DrawBackground(SDL_Renderer* renderer);
		void DrawHealth(SDL_Renderer* renderer);
		void DrawStamina(SDL_Renderer* renderer);
		void DrawXP(SDL_Renderer* renderer);
		void DrawLevel(SDL_Renderer* renderer);
		void DrawHealthBars(SDL_Renderer* renderer);
		void DrawHealthBar(SDL_Renderer* renderer, GameObject* obj);
		float GetScaleX();
		float GetScaleY();
		
};
