#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Map.h"
#include "AnimatedPlayer.h"
#include "GameView.h"

class View
{
	public:
		const int WINDOW_WIDTH;
		const int WINDOW_HEIGHT;

		View();
		View(unsigned int, unsigned int, char*);
		~View();

		int InitView();
		int LoadMap(Map* map);
		int LoadPlayer(AnimatedPlayer* player);
		void Update(float);
		void Start();

	private:
		GameView* GView;

		int CreateWindow();
		int CreateSurface();
		int CreateRenderer();
		SDL_Texture* LoadTexture(char*);
		int InitSDLImage();
		void LoadTextures();

		char* WINDOW_TITLE;

		float Scale;

};
