#pragma once
#include <SDL2/SDL.h>

class GameObject
{
	public:
		enum States { STANDING, RUNNING, JUMPING, FALLING, ATTACKING, DEAD };

		virtual void Update(float dTime) = 0;
        virtual char* getName();
		virtual int getX() = 0;
		virtual int getY() = 0;
		virtual int getState() = 0;
		virtual int getDir() = 0;
		virtual char* GetSpriteSheetPath() = 0;
		virtual SDL_Texture* GetSpriteSheet() = 0;
		virtual void SetSpriteSheet(SDL_Texture* texture) = 0;
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual float getHealth() = 0;
		virtual int getMaxHealth() = 0;

		const int NUM_FRAMES = 8;
		bool active = true;
		bool animStopped = false;
};
