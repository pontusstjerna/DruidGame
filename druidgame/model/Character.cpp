#include "Character.h"
#include <stdio.h>
#include "../util/Geometry.h";

Character::Character(int x, int y, char const* name) : X(x), Y(y), name(name) {

}

Character::~Character() {
	printf("Character destroyed at pos (%f, %f).\n", X, Y);
    delete meleeWeapon;
}

void Character::update(float dTime)
{
	deltaTime = dTime;

	if (collisions[BOTTOM])	{
		yVel = 0;
		consumedJumpPwr = 0;
	}
    
    if (meleeWeapon != NULL) {
        meleeWeapon->update(dTime);
    }

	if (gravityEnabled)
		applyGravity();
		
	if (health <= 0) {
        setState(DEAD);
	}
    
    // TODO remove?
    //collisions[BOTTOM] = false;
}

void Character::clearCollisions() {
    collisions[BOTTOM] = false;
}

void Character::collide(bool newCollisions[4], float correction) {
    for (int i = 0; i < 4; i++) {
        collisions[i] = newCollisions[i];
    }

    
    if (collisions[TOP] || collisions[BOTTOM]) {
        Y = correction;
    } else {
        X = correction;
    }
}

char const* Character::getName() {
    return name;
}

int Character::getX()
{
	return (int)X;
}

int Character::getY()
{
	return (int)Y;
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
	if (!collisions[LEFT])
	{
		X -= deltaTime * speed;

		if (collisions[BOTTOM])
			setState(RUNNING);

		Dir = LEFT;
	}
}

void Character::right() {
	if (!collisions[RIGHT]) {
        
		X += deltaTime * speed;
        
        if (collisions[BOTTOM]) {
            setState(RUNNING);
        }
			

		Dir = RIGHT;
	}
}

int jumps = 0;

void Character::jump() {
    
    // Basic conditions
	if (currState != FALLING && !jumpLock) {
        
        // The actual jumping
        if(!collisions[TOP]) {
            yVel = jumpVel - consumedJumpPwr;
            Y -= deltaTime * yVel;
            jumps++;
        }
        
		consumedJumpPwr += GRAVITY;
        
		if (consumedJumpPwr >= jumpVel || collisions[TOP]) {
            setState(FALLING);
			jumpLock = true;
		} else {
            setState(JUMPING);
            printf("Setstate JUMPING\n");
		}
	}
}

void Character::Stop()
{
	if (collisions[BOTTOM] || collisions[LEFT] || collisions[RIGHT])
		setState(STANDING);
	else
		setState(FALLING);
}

void Character::stopJump()
{
	jumpLock = false;

	if(!collisions[BOTTOM])
		currState = FALLING;
}

MeleeWeapon* Character::getMeleeWeapon() {
    return meleeWeapon;
}

void Character::attack() {
    if (meleeWeapon != NULL) {
        meleeWeapon->attack();
    }
}

void Character::damage(float dmg)
{
	health -= dmg;
}

void Character::SetGravity(bool gravity)
{
	gravityEnabled = gravity;
}

int Character::getMaxHealth()
{
	return MaxHealth;
}

float Character::getHealth()
{
	return health;
}

int Character::getWidth()
{
	return Width;
}

int Character::getHeight()
{
	return Height;
}

void Character::applyGravity()
{
	if (!collisions[BOTTOM] && currState != JUMPING)
	{
		Y += deltaTime * yVel;
		yVel += GRAVITY;
	}
}

int Character::getYVel()
{
	return yVel;
}

float Character::Distance(float x, float y)
{
    return Geometry::distance(X, Y, x, y);
}

void Character::setState(States state)
{
    if (currState != DEAD) {
        lastState = currState;
        currState = state;
    }
}
