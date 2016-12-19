#pragma once
#include <SDL.h>
class Block
{
	public:
		Block(int x, int y, int width, int height, char* texture);
		~Block();

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
		char* TexturePath;
		int X, Y, W, H;
		SDL_Texture* Texture;
};