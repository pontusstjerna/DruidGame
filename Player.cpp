#include "Player.h"
#include <stdio.h>

Player::Player(int x, int y, char** spriteSheets) : Character(x, y)
{
	NumSpriteSheets = 2;

	SpriteSheetPaths = new char*[NumSpriteSheets];
	for (int i = 0; i < NumSpriteSheets; i++)
	{
		SpriteSheetPaths[i] = spriteSheets[i];
	}

	SpriteSheets = new SDL_Texture*[NumSpriteSheets];

	SetStats(HUMAN);
	Health = MaxHealth;
	Stamina = MaxStamina;

	printf("Player created at pos (%i,%i) with stats: \n\tHP: %i\n\tStamina: %i\n", x, y, MaxHealth, MaxStamina);
}

Player::~Player()
{
	for (int i = 0; i < NumSpriteSheets; i++)
	{
		SDL_DestroyTexture(SpriteSheets[i]);
	}
	printf("Player destroyed.\n");
}

void Player::Shapeshift(Forms form)
{
	if (Level >= RequiredLevels[form])
	{
		Form = form;
		SetStats(form);
	}
}

void Player::Update(float dTime)
{
	Character::Update(dTime);

	if (CurrState == HUMAN)
	{
		HealthRegen();
	}

	if (Collisions[BOTTOM])
		StaminaRegen();
}

int Player::GetStamina()
{
	return Stamina;
}

int Player::GetMaxStamina()
{
	return MaxStamina;
}

int Player::GetXP()
{
	return Experience;
}

int Player::GetLevel()
{
	return Level;
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

void Player::SetSpriteSheet(SDL_Texture* spriteSheet, int index)
{
	SpriteSheets[index] = spriteSheet;
}

char** Player::GetSpriteSheetPaths()
{
	return SpriteSheetPaths;
}

void Player::Jump()
{
	if (Stamina > 0)
	{
		if (CurrState == JUMPING)
		{
			const int multiplier = 20;
			Stamina -= DeltaTime*multiplier;
			if (Stamina < 0)
				Stamina = 0;
		}
	}
	else 
	{
		ConsumedJumpPwr = JumpVel;
	}

	Character::Jump();
}

void Player::SetStats(Forms form)
{
	float oldHeight = Height;

	//HELP ALFRED
	switch (form)
	{
	case Player::HUMAN:
		MaxHealth = 50;
		MaxStamina = 50;
		JumpVel = 250;
		Speed = 70;
		Width = 20;
		Height = 40;
		AttackDmg = 3;
		break;
	case Player::CAT:
		MaxHealth = 30;
		MaxStamina = 50;
		JumpVel = 500;
		Speed = 150;
		Width = 50;
		Height = 25;
		AttackDmg = 20;
		break;
	case Player::BEAR:
		MaxHealth = 300;
		MaxStamina = 100;
		JumpVel = 400;
		Speed = 90;
		AttackDmg = 10;
		break;
	case Player::BIRD:
		MaxHealth = 10;
		MaxStamina = 30;
		JumpVel = 0;
		Speed = 400;
		AttackDmg = 1;
		break;
	case Player::FISH:
		break;
	default:
		break;
	}

	if (oldHeight < Height)
		Y -= oldHeight;

	if (Health > MaxHealth)
		Health = MaxHealth;

	if (Stamina > MaxStamina)
		Stamina = MaxStamina;
}

void Player::HealthRegen()
{
	if (Health < MaxHealth)
	{
		Health += DeltaTime;
	}
	else
	{
		Health = MaxHealth;
	}
}

void Player::StaminaRegen()
{
	const int multiplier = 3;
	if (Stamina < MaxStamina)
	{
		Stamina += DeltaTime*multiplier;
	}
	else
	{
		Stamina = MaxStamina;
	}
}
