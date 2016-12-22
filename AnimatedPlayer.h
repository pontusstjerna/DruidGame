#pragma once
#include "AnimatedObject.h"

class AnimatedPlayer
{
	public:
		virtual SDL_Texture** GetSpriteSheets() = 0;
		virtual int GetNumSpriteSheets() = 0;
		virtual int GetActiveSpriteSheet() = 0;


};