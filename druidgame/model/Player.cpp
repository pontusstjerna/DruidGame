#include "Player.h"
#include <stdio.h>

Player::Player(int x, int y) : Character(x, y, "data/spritesheets/player_human.png")
{
	setStats(HUMAN);
	health = MaxHealth;
	maxStamina = stamina;

	printf("Player created at pos (%i,%i) with stats: \n\tHP: %i\n\tStamina: %i\n", x, y, MaxHealth, stamina);
}

void Player::shapeShift(Forms newForm)
{
	if (!(collisions[LEFT] || collisions[RIGHT]) && level > formLevels[newForm]) {
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

	if (form == HUMAN) {
		healthRegen();
	}
    
    if (form == CAT) { // Jump for half of the attack in cat form
        if (meleeWeapon->getTimer() < meleeWeapon->ATTACK_POINT / 3) {
            jump();
        } else if (meleeWeapon->getTimer() < meleeWeapon->ATTACK_POINT) {
            Character::stopJump();
        }
    }

	if (collisions[BOTTOM])
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

void Player::attack() {
    return Character::attack();
}

void Player::jump()
{
	if (maxStamina > 0)
	{
		if (currState == JUMPING)
		{
			const int multiplier = 20;
			maxStamina -= deltaTime*multiplier;
			if (maxStamina < 0)
				maxStamina = 0;
		}
	}
	else 
	{
		consumedJumpPwr = jumpVel;
	}

	Character::jump();
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
		jumpVel = 250;
		speed = 70;
		Width = 20;
		Height = 40;
        // Dmg, range, haste, strength
        meleeWeapon = new MeleeWeapon(10, 10, 200, 0);
		break;
	case Player::CAT:
		MaxHealth = 30;
		stamina = 50;
		jumpVel = 500;
		speed = 150;
		Width = 50;
		Height = 25;
        meleeWeapon = new MeleeWeapon(100, 20, 200, 0);
        //meleeWeapon = new MeleeWeapon(20, 15, 200, 0);
		break;
	case Player::BEAR:
		MaxHealth = 300;
		stamina = 100;
		jumpVel = 400;
		speed = 90;
		break;
	case Player::BIRD:
		MaxHealth = 10;
		stamina = 30;
		jumpVel = 0;
		speed = 400;
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
