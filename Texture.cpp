#include "Texture.h"
#include <stdio.h>

Texture::Texture(SDL_Texture* texture, char* path) : texture(texture), path(path)
{
	printf("Created texture %s.\n", path);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
	printf("Destroyed texture %s.\n",path);
}

SDL_Texture* Texture::getTexture()
{
	return texture;
}
char* Texture::getPath()
{
	return path;
}