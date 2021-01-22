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
	float getX();
	float getY();
	float getWidth();
	float getHeight();
	b2Body *getBody();

	const float MIN_WIDTH = 0.4f;
	const float MIN_HEIGHT = 0.4f;

private:
	char *name;
	float X, Y, W, H;
	b2Body *body;
};

#endif // Block_h
