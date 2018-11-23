#pragma once
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// TODO: Eventually remove this class
class Texture
{
public:
	Texture(SDL_Texture* texture, char* path);
	~Texture();

	SDL_Texture* getTexture();
	char* getName();

private:

	SDL_Texture* texture;
	char* name;
};
