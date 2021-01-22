#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "../view/AnimatedPlayer.h"
#include <box2d/box2d.h>

class Player : public AnimatedPlayer, public Character
{
public:
	enum Forms
	{
		HUMAN,
		CAT,
		BEAR,
		FISH,
		BIRD
	};

	Player(int x, int y, b2World *world);

	void jump();

	void shapeShift(Forms form);
	void attack();
	int getStamina();
	int getMaxStamina();
	int getXP();
	int getLevel();

	void update(float dTime);
	char const *getName();

	//Refer these functions to character base class
	float getX() { return Character::getX(); };
	float getY() { return Character::getY(); };
	int getState() { return Character::getState(); };
	int getDir() { return Character::getDir(); };
	float getWidth() { return Character::getWidth(); };
	float getHeight() { return Character::getHeight(); };
	float getHealth() { return Character::getHealth(); };
	int getMaxHealth() { return Character::getMaxHealth(); };

private:
	const int formLevels[5] = {1, 3, 5, 7, 15};

	int stamina = 100;
	float maxStamina = stamina;

	Forms form = HUMAN;

	int experience = 0;
	int level = 20;

	void setStats(Forms form);
	void healthRegen();
	void staminaRegen();
};
#endif /* PLAYER_H */
