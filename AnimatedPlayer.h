#pragma once

#include "AnimatedObject.h"

class AnimatedPlayer : public AnimatedObject
{
	public:
		virtual void SetSpriteSheet(SDL_Texture*, int) = 0;
		virtual char** GetSpriteSheetPaths() = 0;
		virtual SDL_Texture** GetSpriteSheets() = 0;
		virtual int GetNumSpriteSheets() = 0;
		virtual int GetActiveSpriteSheet() = 0;

};