#include "Character.h"
#include <stdio.h>

Character::Character(int x, int y, char* spriteSheet) : X(x), Y(y), SpriteSheetPath(spriteSheet)
{
	
}

//Constructor for more than one spritesheets
Character::Character(int x, int y) : X(x), Y(y) {}

Character::~Character()
{
	printf("Character destroyed at pos (%i, %i).\n", X, Y);
}

void Character::Update(float dTime)
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

}

void Character::Collide(Direction dir, bool collide)
{
	Collisions[dir] = collide;
}

int Character::GetX()
{
	return (int)X;
}

int Character::GetY()
{
	return (int)Y;
}

int Character::GetState()
{
	return CurrState;
}

int Character::GetDir()
{
	return Dir;
}

char* Character::GetSpriteSheetPath()
{
	return SpriteSheetPath;
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

		if(Collisions[BOTTOM])
			CurrState = RUNNING;

		Dir = LEFT;
	}
}

void Character::MoveRight()
{
	if (!Collisions[RIGHT])
	{
		X += DeltaTime*Speed;
		if(Collisions[BOTTOM])
			CurrState = RUNNING;

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
	}
}

void Character::Stop()
{
	if (Collisions[BOTTOM])
		CurrState = STANDING;
	else
		CurrState = FALLING;
}

void Character::StopJump()
{
	JumpLock = false;
	CurrState = FALLING;
}

void Character::Attack()
{
	//ClosestCharacter()->Damage(AttackDmg);
}

void Character::Damage(float dmg)
{
	Health -= dmg;
	if (Health <= 0)
	{
		Die();
	}
	//CurrState = DYING;
}

void Character::SetGravity(bool gravity)
{
	GravityEnabled = gravity;
}

int Character::GetMaxHealth()
{
	return MaxHealth;
}

int Character::GetHealth()
{
	return Health;
}

int Character::GetWidth()
{
	return Width;
}

int Character::GetHeight()
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

void Character::Die()
{
	//Oops
}