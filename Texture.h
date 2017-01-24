#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Texture
{
public:
	Texture(SDL_Texture* texture, char* path);
	~Texture();

	SDL_Texture* getTexture();
	char* getPath();

private:

	SDL_Texture* texture;
	char* path;
};