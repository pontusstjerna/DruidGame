#pragma once
#include "Character.h"
#include "AnimatedPlayer.h"

class Player : public AnimatedPlayer, public Character
{
	public:
		enum Forms {HUMAN, CAT, BEAR, FISH, BIRD};

		Player(int x, int y, char**);
		~Player();

		void Shapeshift(Forms form);
		int GetXP();
		int GetLevel();

		int GetActiveSpriteSheet();

		SDL_Texture** AnimatedPlayer::GetSpriteSheets();
		int AnimatedPlayer::GetNumSpriteSheets();
		int GetActiveSpriteSheet();
		
	private:
		const int RequiredLevels[5] = { 1, 3, 5, 7, 15 };

		int MaxStamina = 100;
		float Stamina = MaxStamina;

		Forms Form = HUMAN;

		int Experience = 0;
		int Level = 20;

		void SetStats(Forms form);

		char** SpriteSheetPaths;
		SDL_Texture** SpriteSheets;
		int NumSpriteSheets;
};