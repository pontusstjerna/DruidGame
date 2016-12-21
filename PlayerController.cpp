#include "PlayerController.h"
#include <stdio.h>



PlayerController::PlayerController(Player* player) : ActivePlayer(player)
{
	
}

void PlayerController::UpdateInputs(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		AddKeyPress(e.key.keysym.sym);
	}
	else if (e.type == SDL_KEYUP)
	{
		RemoveKeyPress(e.key.keysym.sym);
	}
}

void PlayerController::Update()
{
	if (Presses[RIGHT])
	{
		ActivePlayer->MoveRight();
	}
	else if (Presses[LEFT])
	{
		ActivePlayer->MoveLeft();
	}

	if (Presses[UP])
	{
		ActivePlayer->Jump();
	}

	bool empty = true;
	for (int i = 0; i < sizeof(Presses); i++)
	{
		if (Presses[i])
			empty = false;
	}

	if (empty)
		ActivePlayer->Stop();
}

void PlayerController::AddKeyPress(SDL_Keycode code)
{
	switch (code)
	{
		case SDLK_RIGHT:
			if (!Presses[RIGHT])
				Presses[RIGHT] = true;
			break;
		case SDLK_LEFT:
			if (!Presses[LEFT])
				Presses[LEFT] = true;
			break;
		case SDLK_UP:
			if (!Presses[UP])
				Presses[UP] = true;
			break;
	}
}

void PlayerController::RemoveKeyPress(SDL_Keycode code)
{
	switch (code)
	{
		case SDLK_RIGHT:
				Presses[RIGHT] = false;
			break;
		case SDLK_LEFT:
				Presses[LEFT] = false;
			break;
		case SDLK_UP:
				Presses[UP] = false;
			break;
	}
}