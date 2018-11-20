#pragma once

#include "Character.h"

class AnimatedPlayer : public GameObject
{
	public:
		virtual void SetSpriteSheet(SDL_Texture*, int) = 0;
		virtual char** GetSpriteSheetPaths() = 0;
		virtual SDL_Texture** GetSpriteSheets() = 0;
		virtual int GetNumSpriteSheets() = 0;
		virtual int GetActiveSpriteSheet() = 0;
		virtual int GetStamina() = 0;
		virtual int GetMaxStamina() = 0;
		virtual int GetLevel() = 0;
		virtual int GetXP() = 0;

};
