#pragma once
#include "Character.h"
#include "AnimatedPlayer.h"

class Player : public AnimatedPlayer, public Character
{
	public:
		enum Forms {HUMAN, CAT, BEAR, FISH, BIRD};

		Player(int x, int y);

		void Jump();

		void Shapeshift(Forms form);
		int GetStamina();
		int GetMaxStamina();
		int GetXP();
		int GetLevel();
    
        void update(float dTime);
        char* getName();

		//Refer these functions to character base class
		int getX() { return Character::getX(); };
		int getY() { return Character::getY(); };
		int getState() { return Character::getState(); };
		int getDir() { return Character::getDir(); };
		int getWidth() { return Character::getWidth(); };
		int getHeight() { return Character::getHeight(); };
		float getHealth() { return Character::getHealth(); };
        int getMaxHealth() { return Character::getMaxHealth(); };
		
	private:
		const int RequiredLevels[5] = { 1, 3, 5, 7, 15 };

		int MaxStamina = 100;
		float Stamina = MaxStamina;
		bool tryShift = false;

		Forms form = HUMAN;

		int Experience = 0;
		int Level = 20;

		void SetStats(Forms form);
		void HealthRegen();
		void StaminaRegen();
};
