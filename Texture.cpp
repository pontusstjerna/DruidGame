//#include <stdio.h>
//#include "Texture.h"
//
//Texture::Texture(char* path) 
//{
//	MainTexture = LoadTexture(path);
//}
//
//Texture::~Texture()
//{
//
//}
//
//void Texture::Render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip)
//{
//	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
//
//	//Set clip rendering dimensions
//	if (clip != NULL)
//	{
//		renderQuad.w = clip->w;
//		renderQuad.h = clip->h;
//	}
//
//	//Render to screen
//	SDL_RenderCopy(renderer, MainTexture, clip, &renderQuad);
//}
//
//SDL_Texture* Texture::LoadTexture(char* path)
//{
//	SDL_Texture* texture = NULL;
//
//	SDL_Surface* tmpSurface = IMG_Load(path);
//
//	if (tmpSurface == NULL)
//		printf("Unable to load image: %s. \nCause: %s\n", path, SDL_GetError());
//
//	texture = SDL_CreateTextureFromSurface(Renderer, tmpSurface);
//	if (texture == NULL)
//		printf("Unable to load texture. \nCause: %s\n", SDL_GetError());
//
//	//Reallocate
//	SDL_FreeSurface(tmpSurface);
//
//	return texture;
//}
