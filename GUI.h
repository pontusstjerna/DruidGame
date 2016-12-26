#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "AnimatedPlayer.h"
#include "AnimatedObject.h"
#include "View.h"

class GUI
{
	public:
		GUI(AnimatedPlayer* player, int nObjects, AnimatedObject**);
		~GUI();

		int LoadGUI(char* background);

		void Update(float dTime);

	private:
		AnimatedPlayer* Player;
		AnimatedObject** Objects;

		SDL_Texture* Background = NULL;

		int NumObjects = 0;
};