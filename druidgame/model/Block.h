#pragma once
#include <SDL2/SDL.h>
#include "Entity.h"

class Block : Entity
{
	public:
		Block(int x, int y, int width, int height, char* texture);
		~Block();

        char* getName();
		int GetX();
		int GetY();
		int GetWidth();
		int GetHeight();
		char* GetTexturePath();
		SDL_Texture* GetTexture();
		void SetTexture(SDL_Texture* texture);

		const int MIN_WIDTH = 10;
		const int MIN_HEIGHT = 10;

	private:
		char* name;
		int X, Y, W, H;
		SDL_Texture* Texture;
};
