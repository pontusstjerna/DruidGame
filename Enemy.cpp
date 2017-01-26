#include "Enemy.h"

Enemy::Enemy(int x, int y, char* texture, int seedSeparator) : Character(x,y,texture), startX(x), startY(y)
{

	srand(time(NULL) + seedSeparator);
	direction = rand() % 2;
	turnTime = (rand() + minDirTime) % maxDirTime;

	Speed = 50;
}

Enemy::~Enemy()
{
	Character::~Character();
}

void Enemy::Update(float dTime)
{
	Character::Update(dTime);

	
	if (CurrState != DEAD)
	{
		timer += dTime * 1000;

		DecideDir();
		Walk(direction);

		Health -= 8 * dTime;
	}
}

void Enemy::DecideDir()
{
	if (X - startX > maxDistX || Collisions[RIGHT])
	{
		direction = LEFT;
	}
	else if (startX - X > maxDistX || Collisions[LEFT])
	{
		direction = RIGHT;
	}
	else if (timer > turnTime)
	{
		turnTime = (rand() + minDirTime) % maxDirTime;
		timer = 0;

		if (direction == LEFT)
			direction = RIGHT;
		else
			direction = LEFT;
	}
}

void Enemy::Walk(int dir)
{
	switch (dir)
	{
		case LEFT:
			MoveLeft();
			break;
		case RIGHT:
			MoveRight();
			break;
	}
}
