#pragma once
#include "GameObject.h"

class Character : public GameObject
{
	public:
		enum Direction {RIGHT, LEFT, TOP, BOTTOM};

		Character(int x, int y, char* spriteSheet);
		Character(int x, int y);
		~Character();
		void Update (float dTime);
		int getX();
		int getY();
		int getState();
		int getDir();
		char* GetSpriteSheetPath();
		SDL_Texture* GetSpriteSheet();
		void SetSpriteSheet(SDL_Texture* texture);
		int getWidth();
		int getHeight();
		float getHealth();
		int getMaxHealth();
		float Distance(float x, float y);

		void Collide(Direction dir, bool collide);
		void MoveLeft();
		void MoveRight();
		void Jump();
		void Stop();
		void StopJump();
		void Attack(Character* target);
		void Damage(float dmg);
		void SetGravity(bool gravity);
		int GetFallingVel();

	protected:
		float X, Y;
		float DeltaTime = 0;

		int MaxHealth = 100;
		float health = MaxHealth;
		int Speed = 100;
		int JumpVel = 300;
		float ConsumedJumpPwr = 0;
		float AttackDmg = 3;
		float AttackRange = 30;
		float attackCooldown = 0.5;
		float attackTimer = 0;

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
		void SetState(States state);
};
