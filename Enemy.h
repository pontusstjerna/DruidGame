#pragma once
#include "AnimatedObject.h"

class Enemy : AnimatedObject
{
	public:	
		Enemy(char* json);
		~Enemy();
};