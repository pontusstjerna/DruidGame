#pragma once
#include "Player.h"
#include <SDL.h>
class PlayerController
{
	public:
		PlayerController(Player* player);
		void UpdateInputs(SDL_Event e);
		void Update();

	private:
		enum KeyPos { RIGHT, LEFT, UP };
		Player* ActivePlayer;
		bool Presses[3] = {false, false, false};

		void AddKeyPress(SDL_Keycode code);
		void RemoveKeyPress(SDL_Keycode code);
};