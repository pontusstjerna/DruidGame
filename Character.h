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
		int AnimatedObject::GetHealth();
		int AnimatedObject::GetMaxHealth();

		void Collide(Direction dir, bool collide);
		void MoveLeft();
		void MoveRight();
		void Jump();
		void Stop();
		void StopJump();
		void Attack();
		void Damage(float dmg);
		void SetGravity(bool gravity);
		int GetFallingVel();

	protected:
		float X, Y;
		float DeltaTime = 0;

		int MaxHealth = 100;
		float Health = MaxHealth;
		int Speed = 100;
		int JumpVel = 300;
		float ConsumedJumpPwr = 0;
		float AttackDmg = 3;
		float AttackRange = 10;

		bool GravityEnabled = true;

		int Width = 20;
		int Height = 40;

		States CurrState = STANDING;
		States TempState = STANDING;
		Direction Dir = RIGHT;

		bool Collisions[4];

		char* SpriteSheetPath;
		SDL_Texture* SpriteSheet;

		void Die();

	private:
		const int GRAVITY_INCREASE = 1500;
		
		bool JumpLock = false;
		int Gravity = 0;

		void ApplyGravity();
};