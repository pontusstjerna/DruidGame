#include "PlayerController.h"
#include <stdio.h>



PlayerController::PlayerController(World* world) : world(world)
{
	player = world->GetPlayer();
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
		player->MoveRight();
	}
	else if (Presses[LEFT])
	{
		player->MoveLeft();
	}

	if (Presses[UP])
	{
		player->Jump();
	}

	bool empty = true;
	for (int i = 0; i < sizeof(Presses); i++)
	{
		if (i != UP && Presses[i])
			empty = false;
	}

	if (empty)
		player->Stop();
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
				player->StopJump();
			break;
		case SDLK_SPACE:
			player->Attack(world->GetClosestCharacter(player));
			break;
		case SDLK_1:
			player->Shapeshift(Player::HUMAN);
			break;
		case SDLK_2:
			player->Shapeshift(Player::CAT);
			break;
		case SDLK_3:
			player->Shapeshift(Player::BEAR);
			break;
		case SDLK_4:
			player->Shapeshift(Player::FISH);
			break;
		case SDLK_5:
			player->Shapeshift(Player::BIRD);
			break;
	}
}