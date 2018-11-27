#pragma once
#include "../model/Player.h"
#include "../model/World.h"
#include <SDL2/SDL.h>
class PlayerController
{
	public:
		PlayerController(World* world);
		void checkInputs(SDL_Event e);
		void update();

	private:
		enum KeyPos { RIGHT, LEFT, UP, SPACE};
		Player* player;
		World* world;
		bool presses[4] = {false, false, false, false};

		void addKeyPress(SDL_Keycode code);
		void RemoveKeyPress(SDL_Keycode code);
};
