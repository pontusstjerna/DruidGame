#include "Enemy.h"

Enemy::Enemy(int x, int y, char* texture) : Character(x,y,texture), startX(x), startY(y)
{
	direction = RIGHT;
}

Enemy::~Enemy()
{
	Character::~Character();
}

void Enemy::Update(float dTime)
{
	Character::Update(dTime);

	DecideDir();
	Walk(direction);
}

void Enemy::DecideDir()
{
	if (X - startX > MAX_DIST_X || Collisions[RIGHT])
	{
		direction = LEFT;
	}
	else if (startX - X > MAX_DIST_X || Collisions[LEFT])
	{
		direction = RIGHT;
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
