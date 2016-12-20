#pragma once
#include "AnimatedObject.h"

class Character : public AnimatedObject
{
	public:
		enum States {STANDING, RUNNING, JUMPING, ATTACKING, DYING};
		enum Direction {RIGHT, LEFT};

		Character(int x, int y, char* spriteSheet);
		~Character();
		void AnimatedObject::Update(float dTime);
		int AnimatedObject::GetX();
		int AnimatedObject::GetY();
		int AnimatedObject::GetState();
		char* AnimatedObject::GetSpriteSheetPath();
		SDL_Texture* AnimatedObject::GetSpriteSheet();
		void AnimatedObject::SetSpriteSheet(SDL_Texture* texture);
		int AnimatedObject::GetWidth();
		int AnimatedObject::GetHeight();

		void MoveLeft();
		void MoveRight();
		void Jump();
		void Kill();

		int GetMaxHealth();
		int GetHealth();

	private:
		float DeltaTime = 0;
		float X, Y;
		States state = STANDING;
		float Speed = 1;

		int Width = 20;
		int Height = 40;
		char* SpriteSheetPath;
		SDL_Texture* SpriteSheet = NULL;
};