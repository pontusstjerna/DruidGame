#pragma once
#include "Character.h"
#include "AnimatedPlayer.h"

class Player : public AnimatedPlayer, public Character
{
	public:
		enum Forms {HUMAN, CAT, BEAR, FISH, BIRD};

		Player(int x, int y, char**);
		~Player();

		void Jump();

		void Shapeshift(Forms form);
		int AnimatedPlayer::GetStamina();
		int AnimatedPlayer::GetMaxStamina();
		int AnimatedPlayer::GetXP();
		int AnimatedPlayer::GetLevel();

		//Refer these functions to character base class
		void AnimatedPlayer::Update(float dTime);
		int AnimatedPlayer::GetX() { return Character::GetX(); };
		int AnimatedPlayer::GetY() { return Character::GetY(); };
		int AnimatedPlayer::GetState() { return Character::GetState(); };
		int AnimatedPlayer::GetDir() { return Character::GetDir(); };
		char* AnimatedPlayer::GetSpriteSheetPath() { return Character::GetSpriteSheetPath(); };
		SDL_Texture* AnimatedPlayer::GetSpriteSheet() { return Character::GetSpriteSheet(); };
		void AnimatedPlayer::SetSpriteSheet(SDL_Texture* texture, int);
		int AnimatedPlayer::GetWidth() { return Character::GetWidth(); };
		int AnimatedPlayer::GetHeight() { return Character::GetHeight(); };
		float AnimatedPlayer::GetHealth() { return Character::GetHealth(); };
		int AnimatedPlayer::GetMaxHealth() { return Character::GetMaxHealth(); };
		void AnimatedObject::SetSpriteSheet(SDL_Texture* texture) { Character::SetSpriteSheet(texture); };

		int GetActiveSpriteSheet();

		SDL_Texture** AnimatedPlayer::GetSpriteSheets();
		int AnimatedPlayer::GetNumSpriteSheets();
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