#pragma once
#include "AnimatedObject.h"

class Player : AnimatedObject
{
	Player(int x, int y);
	~Player();

	void MoveRight();
	void MoveLeft();
	void Jump();
};