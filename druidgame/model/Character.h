#ifndef CHARACTER_H
#define CHARACTER_H

#include "../model/GameObject.h"
#include "MeleeWeapon.h"
#include <box2d/box2d.h>

class Character : public GameObject
{
public:
	enum Direction
	{
		RIGHT,
		LEFT,
		TOP,
		BOTTOM
	};

	Character(int x, int y, b2World *world, char const *name);
	~Character();
	void update(float dTime);
	b2Body *getBody();
	char const *getName();
	float getX();
	float getY();
	int getState();
	int getDir();
	float getWidth();
	float getHeight();
	float getHealth();
	int getMaxHealth();
	float Distance(float x, float y);

	void left();
	void right();
	void jump();
	void Stop();
	void stopJump();
	MeleeWeapon *getMeleeWeapon();
	void attack();
	void damage(float dmg);

protected:
	float deltaTime = 0;

	int MaxHealth = 100;
	float health = MaxHealth;
	int speed = 100;
	int jumpVel = 300;
	float consumedJumpPwr = 0;

	MeleeWeapon *meleeWeapon = NULL;

	float Width = 0.9f;
	float Height = 1.8f;

	States currState = STANDING;
	States lastState = STANDING;
	Direction Dir = RIGHT;

	char const *name;

	void Die();

private:
	b2Body *body;
	bool jumpLock = false;

	void setState(States state);
};
#endif /* CHARACTER_H */
