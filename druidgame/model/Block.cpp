#include "Block.h"

Block::Block(int x, int y, int width, int height, b2World *world, char *name) : name(name)
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

	// Adjust to real coordinates
	// This is to allow for block "snapping" in its own grid
	W = width * MIN_WIDTH;
	H = height * MIN_HEIGHT;

	// Translate origin to center instead of top left corner
	X = x * MIN_WIDTH + (W / 2);
	Y = y * MIN_HEIGHT + (H / 2);

	b2BodyDef bodyDef;
	bodyDef.position.Set(X, Y);

	body = world->CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox(W / 2, H / 2);
	body->CreateFixture(&box, 0.0f);
}

Block::~Block()
{
	body = NULL;
}

char const *Block::getName()
{
	return name;
}

float Block::getX()
{
	return X;
}
float Block::getY()
{
	return Y;
}

float Block::getWidth()
{
	return W;
}

float Block::getHeight()
{
	return H;
}

b2Body *Block::getBody()
{
	return body;
}
