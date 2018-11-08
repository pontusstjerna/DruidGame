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
	if (attackTimer > 0)
		attackTimer -= dTime;
	else if (attackTimer < 0)
	{
		attackTimer = 0;
		CurrState = TempState;
	}
		
	if (Health <= 0)
	{
		CurrState = DEAD;
	}

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
	Health -= dmg;
}

void Character::SetGravity(bool gravity)
{
	GravityEnabled = gravity;
}

int Character::GetMaxHealth()
{
	return MaxHealth;
}

float Character::GetHealth()
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