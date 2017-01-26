#pragma once
#include <ctime>
#include <stdlib.h>
#include "Character.h"

class Enemy : public Character
{
	public:	
		Enemy(int x, int y, char* json, int seedSeparator);
		~Enemy();

		void Update(float dTime);

	private:
		int startX, startY;
		int direction = LEFT;
		int maxDistX = 20000;

		int minDirTime = 1000;
		int maxDirTime = 10000;
		int turnTime = 0;
		float timer = 0;

		void DecideDir();
		void Walk(int dir);
};