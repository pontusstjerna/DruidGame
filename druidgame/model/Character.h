#pragma once
#include "../model/GameObject.h"
#include "MeleeWeapon.h"

class Character : public GameObject
{
	public:
		enum Direction {RIGHT, LEFT, TOP, BOTTOM};

		Character(int x, int y, char const* name);
		~Character();
		void update (float dTime);
        char const* getName();
		int getX();
		int getY();
		int getState();
		int getDir();
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
		void stopJump();
        MeleeWeapon* getMeleeWeapon();
		void attack(Character* target);
        void attack();
		void damage(float dmg);
		void SetGravity(bool gravity);
		int GetFallingVel();

	protected:
		float X, Y;
		float deltaTime = 0;

		int MaxHealth = 100;
		float health = MaxHealth;
		int Speed = 100;
		int JumpVel = 300;
		float ConsumedJumpPwr = 0;
    
        MeleeWeapon* meleeWeapon = NULL;
    
		float attackDmg = 3;
		float attackRange = 30;
		float attackCooldown = 0.5;
		float attackTimer = 0;

		bool gravityEnabled = true;

		int Width = 20;
		int Height = 40;

		States currState = STANDING;
		States TempState = STANDING;
		Direction Dir = RIGHT;

		bool Collisions[4];

		char const* name;

		void Die();

	private:
		const int GRAVITY_INCREASE = 1500;
		
		bool JumpLock = false;
		int Gravity = 0;

		void applyGravity();
		void SetState(States state);
};
