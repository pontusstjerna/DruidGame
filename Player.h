#pragma once
#include "Character.h"
#include "AnimatedPlayer.h"

class Player : public AnimatedPlayer
{
	public:
		enum Forms {HUMAN, CAT, BEAR, FISH, BIRD};

		Player(int x, int y, char**);
		~Player();

		void Update(float dTime);
		void Jump();

		void Shapeshift(Forms form);
		int AnimatedPlayer::GetStamina();
		int AnimatedPlayer::GetMaxStamina();
		int AnimatedPlayer::GetXP();
		int AnimatedPlayer::GetLevel();

		int GetActiveSpriteSheet();

		SDL_Texture** AnimatedPlayer::GetSpriteSheets();
		int AnimatedPlayer::GetNumSpriteSheets();
		void SetSpriteSheet(SDL_Texture*, int);
		char** GetSpriteSheetPaths();
		
	private:
		const int RequiredLevels[5] = { 1, 3, 5, 7, 15 };

		int MaxStamina = 100;
		float Stamina = MaxStamina;

		Forms Form = HUMAN;

		int Experience = 0;
		int Level = 20;

		void SetStats(Forms form);
		void HealthRegen();
		void StaminaRegen();

		char** SpriteSheetPaths;
		SDL_Texture** SpriteSheets;
		int NumSpriteSheets;
};