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

	if (Collisions[BOTTOM])
	{
		Gravity = 0;
		ConsumedJumpPwr = 0;
	}
    
    if (meleeWeapon != NULL) {
        meleeWeapon->update(dTime);
    }

	if (gravityEnabled)
		applyGravity();

	//printf("State: %i\n", CurrState);
	if (attackTimer > 0)
		attackTimer -= dTime;
	else if (attackTimer < 0)
	{
		attackTimer = 0;
		currState = TempState;
	}
		
	if (health <= 0)
	{
		currState = DEAD;
	}

}

void Character::Collide(Direction dir, bool collide)
{
	Collisions[dir] = collide;
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

void Character::MoveLeft()
{
	if (!Collisions[LEFT])
	{
		X -= deltaTime*Speed;

		if (Collisions[BOTTOM])
			SetState(RUNNING);

		Dir = LEFT;
	}
}

void Character::MoveRight()
{
	if (!Collisions[RIGHT])
	{
		X += deltaTime*Speed;
		if (Collisions[BOTTOM])
			SetState(RUNNING);

		Dir = RIGHT;
	}
}

void Character::Jump()
{
	if (ConsumedJumpPwr == 0 && currState != FALLING)
		TempState = currState;

	if (currState != FALLING && !JumpLock)
	{
		if(!Collisions[TOP])
			Y -= deltaTime*(JumpVel - ConsumedJumpPwr);

		ConsumedJumpPwr += GRAVITY_INCREASE * deltaTime;

		if (ConsumedJumpPwr > JumpVel || Collisions[TOP])
		{
			currState = FALLING;
			JumpLock = true;
		}
		else
		{
			currState = JUMPING;
		}
	}
	else if(Collisions[BOTTOM])
	{
		currState = TempState;
		TempState = STANDING;
	}
}

void Character::Stop()
{
	if (Collisions[BOTTOM] || Collisions[LEFT] || Collisions[RIGHT])
		SetState(STANDING);
	else
		SetState(FALLING);
}

void Character::stopJump()
{
	JumpLock = false;

	if(!Collisions[BOTTOM])
		currState = FALLING;
}

MeleeWeapon* Character::getMeleeWeapon() {
    return meleeWeapon;
}

void Character::attack(Character* target)
{
	if (attackTimer == 0)
	{
		currState = ATTACKING;
		attackTimer = attackCooldown;
	}
	
	int x = X;
	if (Dir == RIGHT)
		x += Width;

	if(target->Distance(x,Y) < attackRange)
		target->damage(attackDmg);
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
	if (!Collisions[BOTTOM] && currState != JUMPING)
	{
		Y += deltaTime*Gravity;
		Gravity += GRAVITY_INCREASE * deltaTime;
	}
}

int Character::GetFallingVel()
{
	return Gravity;
}

float Character::Distance(float x, float y)
{
    return Geometry::distance(X, Y, x, y);
}

void Character::SetState(States state)
{
	if (state == STANDING && currState == ATTACKING)
		return;

	if (currState != ATTACKING && TempState != STANDING)
	{
		currState = TempState;
		TempState = STANDING;
	}
		
	 if(state != TempState)
		TempState = state;
	 else
		 currState = state;
}
