#include "Character.h"
#include <stdio.h>

Character::Character(int x, int y, char* spriteSheet) : X(x), Y(y), name(spriteSheet)
{
	
}

Character::~Character()
{
	printf("Character destroyed at pos (%f, %f).\n", X, Y);
}

void Character::update(float dTime)
{
	DeltaTime = dTime;

	if (Collisions[BOTTOM])
	{
		Gravity = 0;
		ConsumedJumpPwr = 0;
	}	

	if (GravityEnabled)
		ApplyGravity();

	//printf("State: %i\n", CurrState);
	if (attackTimer > 0)
		attackTimer -= dTime;
	else if (attackTimer < 0)
	{
		attackTimer = 0;
		CurrState = TempState;
	}
		
	if (health <= 0)
	{
		CurrState = DEAD;
	}

}

void Character::Collide(Direction dir, bool collide)
{
	Collisions[dir] = collide;
}

char* Character::getName() {
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
	return CurrState;
}

int Character::getDir()
{
	return Dir;
}

char* Character::GetSpriteSheetPath()
{
	return name;
}

SDL_Texture* Character::GetSpriteSheet()
{
	return SpriteSheet;
}

void Character::SetSpriteSheet(SDL_Texture* texture)
{
	SpriteSheet = texture;
}

void Character::MoveLeft()
{
	if (!Collisions[LEFT])
	{
		X -= DeltaTime*Speed;

		if (Collisions[BOTTOM])
			SetState(RUNNING);

		Dir = LEFT;
	}
}

void Character::MoveRight()
{
	if (!Collisions[RIGHT])
	{
		X += DeltaTime*Speed;
		if (Collisions[BOTTOM])
			SetState(RUNNING);

		Dir = RIGHT;
	}
}

void Character::Jump()
{
	if (ConsumedJumpPwr == 0 && CurrState != FALLING)
		TempState = CurrState;

	if (CurrState != FALLING && !JumpLock)
	{
		if(!Collisions[TOP])
			Y -= DeltaTime*(JumpVel - ConsumedJumpPwr);

		ConsumedJumpPwr += GRAVITY_INCREASE * DeltaTime;

		if (ConsumedJumpPwr > JumpVel || Collisions[TOP])
		{
			CurrState = FALLING;
			JumpLock = true;
		}
		else
		{
			CurrState = JUMPING;
		}
	}
	else if(Collisions[BOTTOM])
	{
		CurrState = TempState;
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

void Character::StopJump()
{
	JumpLock = false;

	if(!Collisions[BOTTOM])
		CurrState = FALLING;
}

void Character::Attack(Character* target)
{
	if (attackTimer == 0)
	{
		CurrState = ATTACKING;
		attackTimer = attackCooldown;
	}
	
	int x = X;
	if (Dir == RIGHT)
		x += Width;

	if(target->Distance(x,Y) < AttackRange)
		target->Damage(AttackDmg);
}

void Character::Damage(float dmg)
{
	health -= dmg;
}

void Character::SetGravity(bool gravity)
{
	GravityEnabled = gravity;
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

void Character::ApplyGravity()
{
	if (!Collisions[BOTTOM] && CurrState != JUMPING)
	{
		Y += DeltaTime*Gravity;
		Gravity += GRAVITY_INCREASE * DeltaTime;
	}
}

int Character::GetFallingVel()
{
	return Gravity;
}

float Character::Distance(float x, float y)
{
	return sqrt(pow(x - X, 2) + pow(y - Y, 2));
}

void Character::SetState(States state)
{
	if (state == STANDING && CurrState == ATTACKING)
		return;

	if (CurrState != ATTACKING && TempState != STANDING)
	{
		CurrState = TempState;
		TempState = STANDING;
	}
		
	 if(state != TempState)
		TempState = state;
	 else
		 CurrState = state;
}
