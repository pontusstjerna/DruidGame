#pragma once
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

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
