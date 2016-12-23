#pragma once
#include "AnimatedObject.h"
#include "AnimatedPlayer.h"

class Character : public AnimatedPlayer
{
	public:
		enum States {STANDING, RUNNING, JUMPING, FALLING, ATTACKING, DYING};
		enum Direction {RIGHT, LEFT, TOP, BOTTOM};

		Character(int x, int y, char* spriteSheet);
		Character(int x, int y);
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
		void StopJump();
		void Kill();
		void SetGravity(bool gravity);
		int GetFallingVel();

		int GetMaxHealth();
		int GetHealth();

	protected:
		int MaxHealth = 100;
		int Health = MaxHealth;
		int Speed = 100;
		int JumpVel = 300;

		bool GravityEnabled = true;

		int Width = 20;
		int Height = 40;

		States CurrState = STANDING;
		States TempState = STANDING;
		Direction Dir = RIGHT;

		char* SpriteSheetPath;
		SDL_Texture* SpriteSheet;

	private:
		const int GRAVITY_INCREASE = 1500;

		float DeltaTime = 0;
		float X, Y;
		
		bool JumpLock = false;
		int Gravity = 0;
		
		bool Collisions[4];

		void ApplyGravity();
};