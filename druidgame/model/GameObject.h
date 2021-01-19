#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Entity.h"

class GameObject : Entity
{
public:
	enum States
	{
		STANDING,
		RUNNING,
		JUMPING,
		FALLING,
		ATTACKING,
		DEAD
	};

	virtual void update(float dTime) = 0;
	virtual char const *getName() = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual int getState() = 0;
	virtual int getDir() = 0;
	virtual float getWidth() = 0;
	virtual float getHeight() = 0;
	virtual float getHealth() = 0;
	virtual int getMaxHealth() = 0;

	const int NUM_FRAMES = 8;
	bool active = true;
	bool animStopped = false;
};
#endif /* GAME_OBJECT_H */
