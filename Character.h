#pragma once
#include "AnimatedObject.h"

class Character : public AnimatedObject
{
	public:
		enum States {STANDING, RUNNING, JUMPING, ATTACKING, DYING};
		enum Direction {RIGHT, LEFT, TOP, BOTTOM};

		Character(int x, int y, char* spriteSheet);
		~Character();
		void AnimatedObject::Update(float dTime);
		int AnimatedObject::GetX();
		int AnimatedObject::GetY();
		int AnimatedObject::GetState();
		int AnimatedObject::GetDir();
		char* AnimatedObject::GetSpriteSheetPath();
		SDL_Texture* AnimatedObject::GetSpriteSheet();
		void AnimatedObject::SetSpriteSheet(SDL_Texture* texture);
		int AnimatedObject::GetWidth();
		int AnimatedObject::GetHeight();

		void Collide(Direction dir, bool collide);
		void MoveLeft();
		void MoveRight();
		void Jump();
		void Stop();
		void Kill();
		void SetGravity(bool gravity);
		int GetFallingVel();

		int GetMaxHealth();
		int GetHealth();

	private:
		float DeltaTime = 0;
		float X, Y;
		States CurrState = STANDING;
		Direction Dir = RIGHT;
		int Speed = 100;
		int Gravity = 0;
		bool GravityEnabled = true;
		bool Collisions[4];

		int Width = 20;
		int Height = 40;
		char* SpriteSheetPath;
		SDL_Texture* SpriteSheet = NULL;

		void ApplyGravity();
};