#include "Block.h"

Block::Block(int x, int y, int width, int height, char* texture) : TexturePath(texture)
{
	//Check valid values
	if (width < 2)
	{
		width = 2;
	}

	if (height < 1)
	{
		height = 1;
	}

	//Adjust to real coordinates
	X = x*MIN_WIDTH;
	Y = y*MIN_HEIGHT;
	W = width*MIN_WIDTH;
	H = height*MIN_HEIGHT;
}

Block::~Block()
{
	SDL_DestroyTexture(Texture);
}

int Block::GetX()
{
	return X;
}
int Block::GetY()
{
	return Y;
}

int Block::GetWidth()
{
	return W;
}

int Block::GetHeight()
{
	return H;
}

char* Block::GetTexturePath()
{
	return TexturePath;
}

SDL_Texture* Block::GetTexture()
{
	return Texture;
}

void Block::SetTexture(SDL_Texture* texture)
{
	Texture = texture;
}