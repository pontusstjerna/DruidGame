#include "Player.h"
#include <stdio.h>

Player::Player(int x, int y) : Character(x, y, "data/spritesheets/player_human.png")
{
	setStats(HUMAN);
	health = MaxHealth;
	maxStamina = stamina;
    meleeWeapon = new MeleeWeapon(20, 200, 0, 1000);

	printf("Player created at pos (%i,%i) with stats: \n\tHP: %i\n\tStamina: %i\n", x, y, MaxHealth, stamina);
}

void Player::shapeShift(Forms newForm)
{
    printf("Shapeshifting from %i to %i\n", this->form, newForm);
	if (!(Collisions[LEFT] || Collisions[RIGHT]) && level > formLevels[newForm]) {
		form = newForm;
		setStats(newForm);
	}
}

char const* Player::getName() {
    switch (form) {
        case HUMAN:
            return "player_human";
        case CAT:
            return "player_cat";
        default:
            return "player_human";
    }
}

void Player::update(float dTime)
{
	Character::update(dTime);

	if (CurrState == HUMAN)
	{
		healthRegen();
	}

	if (Collisions[BOTTOM])
		staminaRegen();
}

int Player::getStamina()
{
	return maxStamina;
}

int Player::getMaxStamina()
{
	return stamina;
}

int Player::getXP()
{
	return experience;
}

int Player::getLevel()
{
	return level;
}

void Player::jump()
{
	if (maxStamina > 0)
	{
		if (CurrState == JUMPING)
		{
			const int multiplier = 20;
			maxStamina -= deltaTime*multiplier;
			if (maxStamina < 0)
				maxStamina = 0;
		}
	}
	else 
	{
		ConsumedJumpPwr = JumpVel;
	}

	Character::Jump();
}

void Player::setStats(Forms form)
{
	float oldHeight = Height;

	//HELP ALFRED
	switch (form)
	{
	case Player::HUMAN:
		MaxHealth = 50;
		stamina = 50;
		JumpVel = 250;
		Speed = 70;
		Width = 20;
		Height = 40;
		attackDmg = 3;
		break;
	case Player::CAT:
		MaxHealth = 30;
		stamina = 50;
		JumpVel = 500;
		Speed = 150;
		Width = 50;
		Height = 25;
		attackDmg = 20;
		break;
	case Player::BEAR:
		MaxHealth = 300;
		stamina = 100;
		JumpVel = 400;
		Speed = 90;
		attackDmg = 10;
		break;
	case Player::BIRD:
		MaxHealth = 10;
		stamina = 30;
		JumpVel = 0;
		Speed = 400;
		attackDmg = 1;
		break;
	case Player::FISH:
		break;
	default:
		break;
	}

	if (oldHeight < Height)
		Y -= oldHeight;

	if (health > MaxHealth)
		health = MaxHealth;

	if (maxStamina > stamina)
		maxStamina = stamina;
}

void Player::healthRegen()
{
	if (health < MaxHealth)
	{
		health += deltaTime;
	}
	else
	{
		health = MaxHealth;
	}
}

void Player::staminaRegen()
{
	const int multiplier = 3;
	if (maxStamina < stamina)
	{
		maxStamina += deltaTime*multiplier;
	}
	else
	{
		maxStamina = stamina;
	}
}
