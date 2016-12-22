#include "Character.h"

float JumpPower = 0;

Character::Character(int x, int y, char* spriteSheet) : X(x), Y(y), SpriteSheetPath(spriteSheet)
{
	
}

//Constructor for more than one spritesheets
Character::Character(int x, int y) : X(x), Y(y) {}

Character::~Character()
{
	SDL_DestroyTexture(SpriteSheet);
}

void Character::Update(float dTime)
{
	DeltaTime = dTime;

	if (Collisions[BOTTOM])
	{
		Gravity = 0;
		JumpPower = 0;
	}
		

	if (GravityEnabled)
		ApplyGravity();

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
		CurrState = RUNNING;
		Dir = LEFT;
	}
}

void Character::MoveRight()
{
	if (!Collisions[RIGHT])
	{
		X += DeltaTime*Speed;
		CurrState = RUNNING;
		Dir = RIGHT;
	}
}

void Character::Jump()
{
	if (JumpPower == 0 && CurrState != FALLING)
		TempState = CurrState;

	if (CurrState != FALLING && !JumpLock)
	{
		if(!Collisions[TOP])
			Y -= DeltaTime*(JumpVel - JumpPower);

		JumpPower += GRAVITY_INCREASE * DeltaTime;

		if (JumpPower > JumpVel || Collisions[TOP])
		{
			CurrState = FALLING;
			JumpLock = true;
		}
		else
			CurrState = JUMPING;
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
}

void Character::Kill()
{
	CurrState = DYING;
}

void Character::SetGravity(bool gravity)
{
	GravityEnabled = gravity;
}

int Character::GetMaxHealth()
{
	return 0;
}

int Character::GetHealth()
{
	return 0;
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