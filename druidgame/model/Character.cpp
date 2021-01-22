#include "Character.h"
#include <stdio.h>
#include "../util/Geometry.h";

Character::Character(int x, int y, b2World *world, char const *name) : name(name)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);

	body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	// TODO: Add width + height
	dynamicBox.SetAsBox(Width / 2.0f, Height / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.1f;

	body->CreateFixture(&fixtureDef);
}

Character::~Character()
{
	printf("Character destroyed at pos (%f, %f).\n", getX(), getY());
	delete meleeWeapon;
}

void Character::update(float dTime)
{
	deltaTime = dTime;

	/*if (collisions[BOTTOM])
	{
		yVel = 0;
		consumedJumpPwr = 0;
	}*/

	if (meleeWeapon != NULL)
	{
		meleeWeapon->update(dTime);
	}

	if (health <= 0)
	{
		setState(DEAD);
	}

	// TODO remove?
	//collisions[BOTTOM] = false;
}

b2Body *Character::getBody()
{
	return body;
}

char const *Character::getName()
{
	return name;
}

float Character::getX()
{
	return (int)body->GetPosition().x;
}

float Character::getY()
{
	return (int)body->GetPosition().y;
}

int Character::getState()
{
	return currState;
}

int Character::getDir()
{
	return Dir;
}

void Character::left()
{
	body->SetLinearVelocity(b2Vec2(-speed, body->GetLinearVelocity().y));
	Dir = LEFT;
	/*if (!collisions[LEFT])
	{
		X -= deltaTime * speed;

		if (collisions[BOTTOM])
			setState(RUNNING);

		Dir = LEFT;
	}*/
}

void Character::right()
{
	body->SetLinearVelocity(b2Vec2(speed, body->GetLinearVelocity().y));
	Dir = RIGHT;

	/*if (!collisions[RIGHT])
	{

		X += deltaTime * speed;

		if (collisions[BOTTOM])
		{
			setState(RUNNING);
		}

		Dir = RIGHT;
	}*/
}

int jumps = 0;

void Character::jump()
{
	body->ApplyForce(b2Vec2(0.0f, -50.0f), body->GetWorldCenter(), true);

	/*
	// Basic conditions
	if (currState != FALLING && !jumpLock)
	{

		// The actual jumping
		if (!collisions[TOP])
		{
			yVel = jumpVel - consumedJumpPwr;
			Y -= deltaTime * yVel;
			jumps++;
		}

		consumedJumpPwr += GRAVITY;

		if (consumedJumpPwr >= jumpVel || collisions[TOP])
		{
			setState(FALLING);
			jumpLock = true;
		}
		else
		{
			setState(JUMPING);
			printf("Setstate JUMPING\n");
		}
	}*/
}

void Character::Stop()
{
	body->SetLinearVelocity(b2Vec2(0.0f, body->GetLinearVelocity().y));
	/*if (collisions[BOTTOM] || collisions[LEFT] || collisions[RIGHT])
		setState(STANDING);
	else
		setState(FALLING);*/
}

void Character::stopJump()
{
	// jumpLock = false;

	// if (!collisions[BOTTOM])
	// 	currState = FALLING;
}

MeleeWeapon *Character::getMeleeWeapon()
{
	return meleeWeapon;
}

void Character::attack()
{
	if (meleeWeapon != NULL)
	{
		meleeWeapon->attack();
	}
}

void Character::damage(float dmg)
{
	health -= dmg;
}

int Character::getMaxHealth()
{
	return MaxHealth;
}

float Character::getHealth()
{
	return health;
}

float Character::getWidth()
{
	return Width;
}

float Character::getHeight()
{
	return Height;
}

float Character::Distance(float x, float y)
{
	return Geometry::distance(getX(), getY(), x, y);
}

void Character::setState(States state)
{
	if (currState != DEAD)
	{
		lastState = currState;
		currState = state;
	}
}
