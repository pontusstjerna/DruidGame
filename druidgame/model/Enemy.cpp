#include "Enemy.h"

Enemy::Enemy(int x, int y, b2World *world, char *texture, int seedSeparator) : Character(x, y, world, texture), startX(x), startY(y)
{

	srand(time(NULL) + seedSeparator);
	direction = rand() % 2;
	turnTime = (rand() + minDirTime) % maxDirTime;

	speed = 50;
}

Enemy::~Enemy()
{
	//Character::~Character();
}

void Enemy::update(float dTime)
{
	Character::update(dTime);

	if (currState != DEAD)
	{
		timer += dTime * 1000;

		DecideDir();
		Walk(direction);
	}
}

void Enemy::DecideDir()
{
	// if (X - startX > maxDistX || collisions[RIGHT])
	// {
	// 	direction = LEFT;
	// }
	// else if (startX - X > maxDistX || collisions[LEFT])
	// {
	// 	direction = RIGHT;
	// }
	// else if (timer > turnTime)
	// {
	// 	turnTime = (rand() + minDirTime) % maxDirTime;
	// 	timer = 0;

	// 	if (direction == LEFT)
	// 		direction = RIGHT;
	// 	else
	// 		direction = LEFT;
	// }
}

void Enemy::Walk(int dir)
{
	switch (dir)
	{
	case LEFT:
		left();
		break;
	case RIGHT:
		right();
		break;
	}
}
