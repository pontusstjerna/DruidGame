#include "Block.h"

Block::Block(int x, int y, int width, int height, char* name) : name(name)
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
    // TODO: Revisit if necessary
	X = x * MIN_WIDTH;
	Y = y * MIN_HEIGHT;
	W = width * MIN_WIDTH;
	H = height * MIN_HEIGHT;
}

char* Block::getName() {
    return name;
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

