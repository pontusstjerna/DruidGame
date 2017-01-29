#pragma once
#include "Player.h"
#include "World.h"
#include <SDL.h>
class PlayerController
{
	public:
		PlayerController(World* world);
		void UpdateInputs(SDL_Event e);
		void Update();

	private:
		enum KeyPos { RIGHT, LEFT, UP, SPACE};
		Player* player;
		World* world;
		bool Presses[4] = {false, false, false, false};

		void AddKeyPress(SDL_Keycode code);
		void RemoveKeyPress(SDL_Keycode code);
};