#include "Texture.h"
#include <stdio.h>

Texture::Texture(SDL_Texture* texture, char* name) : texture(texture), name(name) {
	printf("Created texture for %s.\n", name);
}

Texture::~Texture() {
	SDL_DestroyTexture(texture);
	printf("Destroyed texture %s.\n",name);
}

SDL_Texture* Texture::getTexture() {
	return texture;
}

char* Texture::getName() {
	return name;
}
