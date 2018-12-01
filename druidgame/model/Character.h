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

		void collide(Direction dir, bool collide);
		void left();
		void right();
		void jump();
		void Stop();
		void stopJump();
        MeleeWeapon* getMeleeWeapon();
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
		int jumpVel = 300;
		float consumedJumpPwr = 0;
    
        MeleeWeapon* meleeWeapon = NULL;

		bool gravityEnabled = true;

		int Width = 20;
		int Height = 40;

		States currState = STANDING;
		States lastState = STANDING;
		Direction Dir = RIGHT;

		bool collisions[4];

		char const* name;

		void Die();

	private:
		const int GRAVITY = 30;
		
		bool jumpLock = false;
		int yVel = 0;

		void applyGravity();
		void setState(States state);
};
