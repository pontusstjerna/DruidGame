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

		int LoadGUI(SDL_Texture* background);

		void Update(float dTime);

	private:
		AnimatedPlayer* Player;
		AnimatedObject** Objects;

		SDL_Texture* Background = NULL;

		int NumObjects = 0;
		
};