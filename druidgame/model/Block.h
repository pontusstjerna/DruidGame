#pragma once
#ifndef Block_h
#define Block_h

#include "Entity.h"

class Block : Entity
{
	public:
		Block(int x, int y, int width, int height, char* name);

        char* getName();
		int GetX();
		int GetY();
		int GetWidth();
		int GetHeight();

		const int MIN_WIDTH = 10;
		const int MIN_HEIGHT = 10;

	private:
		char* name;
		int X, Y, W, H;
};

#endif // Block_h
