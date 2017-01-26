#pragma once
#include <SDL.h>

class AnimatedObject
{
	public:
		enum States { STANDING, RUNNING, JUMPING, FALLING, ATTACKING, DEAD };

		virtual void Update(float dTime) = 0;
		virtual int GetX() = 0;
		virtual int GetY() = 0;
		virtual int GetState() = 0;
		virtual int GetDir() = 0;
		virtual char* GetSpriteSheetPath() = 0;
		virtual SDL_Texture* GetSpriteSheet() = 0;
		virtual void SetSpriteSheet(SDL_Texture* texture) = 0;
		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
		virtual float GetHealth() = 0;
		virtual int GetMaxHealth() = 0;

		const int NUM_FRAMES = 8;
		bool active = true;
		bool animStopped = false;
};