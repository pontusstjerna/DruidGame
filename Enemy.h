#pragma once
#include "Character.h"

class Enemy : public Character
{
	public:	
		const int MAX_DIST_X = 200;

		Enemy(int x, int y, char* texture);
		~Enemy();

		void Update(float dTime);

	private:
		int startX, startY;
		int direction = LEFT;

		void DecideDir();
		void Walk(int dir);
};