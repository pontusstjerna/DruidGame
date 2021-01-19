#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "../model/Player.h"
#include "../model/World.h"
#include <SDL2/SDL.h>
class PlayerController
{
public:
	PlayerController(World *world);
	void checkInputs(SDL_Event e);
	void update();

private:
	enum KeyPos
	{
		RIGHT,
		LEFT,
		UP,
		SPACE
	};
	Player *player;
	World *world;
	bool presses[4] = {false, false, false, false};

	void addKeyPress(SDL_Keycode code);
	void removeKeyPress(SDL_Keycode code);
};
#endif /* PLAYER_CONTROLLER_H */
