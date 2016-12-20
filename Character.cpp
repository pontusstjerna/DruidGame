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
	return state;
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
	X -= DeltaTime*Speed;
}

void Character::MoveRight()
{
	X += DeltaTime*Speed;
}

void Character::Jump()
{
	Y -= DeltaTime*Speed;
}

void Character::Kill()
{

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