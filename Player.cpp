#include "Player.h"

Player::Player(int x, int y, char** spriteSheets) : Character(x, y)
{
	NumSpriteSheets = sizeof(spriteSheets);

	SpriteSheetPaths = new char*[NumSpriteSheets];
	for (int i = 0; i < NumSpriteSheets; i++)
	{
		SpriteSheetPaths[i] = spriteSheets[i];
	}

	SpriteSheets = new SDL_Texture*[NumSpriteSheets];

	SetStats(HUMAN);
}

Player::~Player()
{

}

void Player::Shapeshift(Forms form)
{
	if (Level >= RequiredLevels[form])
	{
		Form = form;
		SetStats(form);
	}
}

int Player::GetXP()
{
	return Experience;
}

int Player::GetLevel()
{
	return Level;
}

void Player::SetStats(Forms form)
{
	//HELP ALFRED
	switch (form)
	{
		case Player::HUMAN:
			MaxHealth = 50;
			MaxStamina = 50;
			JumpVel = 250;
			Speed = 70;
			break;
		case Player::CAT:
			MaxHealth = 30;
			MaxStamina = 50;
			JumpVel = 500;
			Speed = 120;
			break;
		case Player::BEAR:
			MaxHealth = 300;
			MaxStamina = 100;
			JumpVel = 400;
			Speed = 90;
			break;
		case Player::BIRD:
			MaxHealth = 10;
			MaxStamina = 30;
			JumpVel = 0;
			Speed = 400;
			break;
		case Player::FISH:
			break;
		default:
			break;
	}
}

int Player::GetActiveSpriteSheet()
{
	return Form;
}

int Player::GetNumSpriteSheets()
{
	return NumSpriteSheets;
}

SDL_Texture** Player::GetSpriteSheets()
{
	return SpriteSheets;
}