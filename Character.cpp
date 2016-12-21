#include "Character.h"

Character::Character(int x, int y, char* spriteSheet) : X(x), Y(y), SpriteSheetPath(spriteSheet)
{

}

Character::~Character()
{
	SDL_DestroyTexture(SpriteSheet);
}

void Character::Update(float dTime)
{
	DeltaTime = dTime;

	if (Collisions[BOTTOM])
		Gravity = 0;

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
	if(!Collisions[LEFT])
		X -= DeltaTime*Speed;

	CurrState = RUNNING;
	Dir = LEFT;
}

void Character::MoveRight()
{
	if(!Collisions[RIGHT])
		X += DeltaTime*Speed;

	CurrState = RUNNING;
	Dir = RIGHT;
}

void Character::Jump()
{
	if(!Collisions[TOP])
		Y -= DeltaTime*Speed;

	CurrState = JUMPING;
}

void Character::Stop()
{
	CurrState = STANDING;
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
	const int gravIncrease = 1500;
	if (!Collisions[BOTTOM] && CurrState != JUMPING)
	{
		Y += DeltaTime*Gravity;
		Gravity += gravIncrease * DeltaTime;
	}
}

int Character::GetFallingVel()
{
	return Gravity;
}