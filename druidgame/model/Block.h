#pragma once
#ifndef Block_h
#define Block_h

#include "Entity.h"
#include <box2d/box2d.h>

class Block : Entity
{
public:
	Block(int x, int y, int width, int height, b2World *world, char *name);
	~Block();

	char const *getName();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	b2Body *getBody();

	const int MIN_WIDTH = 10;
	const int MIN_HEIGHT = 10;

private:
	char *name;
	int X, Y, W, H;
	b2Body *body;
};

#endif // Block_h
