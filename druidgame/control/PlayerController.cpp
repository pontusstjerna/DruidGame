#include "PlayerController.h"
#include <stdio.h>



PlayerController::PlayerController(World* world) : world(world)
{
	player = world->getPlayer();
}

void PlayerController::checkInputs(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		addKeyPress(e.key.keysym.sym);
	}
	else if (e.type == SDL_KEYUP)
	{
		RemoveKeyPress(e.key.keysym.sym);
	}
}

void PlayerController::update()
{
	if (presses[RIGHT])
	{
		player->MoveRight();
	}
	else if (presses[LEFT])
	{
		player->MoveLeft();
	}

	if (presses[UP])
	{
		player->jump();
	}

	bool empty = true;
	for (int i = 0; i < sizeof(presses); i++)
	{
		if (i != UP && presses[i])
			empty = false;
	}

	if (empty)
		player->Stop();
}

void PlayerController::addKeyPress(SDL_Keycode code) {
	switch (code) {
		case SDLK_RIGHT:
			if (!presses[RIGHT])
				presses[RIGHT] = true;
			break;
		case SDLK_LEFT:
			if (!presses[LEFT])
				presses[LEFT] = true;
			break;
		case SDLK_UP:
			if (!presses[UP])
				presses[UP] = true;
			break;
	}
}

void PlayerController::RemoveKeyPress(SDL_Keycode code)
{
	switch (code)
	{
		case SDLK_RIGHT:
				presses[RIGHT] = false;
			break;
		case SDLK_LEFT:
				presses[LEFT] = false;
			break;
		case SDLK_UP:
				presses[UP] = false;
				player->StopJump();
			break;
		case SDLK_SPACE:
			player->attack();
			break;
		case SDLK_1:
			player->shapeShift(Player::HUMAN);
			break;
		case SDLK_2:
			player->shapeShift(Player::CAT);
			break;
		case SDLK_3:
			player->shapeShift(Player::BEAR);
			break;
		case SDLK_4:
			player->shapeShift(Player::FISH);
			break;
		case SDLK_5:
			player->shapeShift(Player::BIRD);
			break;
	}
}
