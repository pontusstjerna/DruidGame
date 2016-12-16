#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Texture
{
public:
	Texture(char* path);
	~Texture();

	void Render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);

	int GetWidth();
	int GetHeight();
private:
	SDL_Texture* LoadTexture(char* path);
	void Free();

	SDL_Texture* MainTexture;

	int mWidth;
	int mHeight;
};