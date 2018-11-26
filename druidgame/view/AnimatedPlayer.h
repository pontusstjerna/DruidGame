#pragma once

#include "Character.h"

class AnimatedPlayer : public GameObject
{
	public:
		virtual int GetStamina() = 0;
		virtual int GetMaxStamina() = 0;
		virtual int GetLevel() = 0;
		virtual int GetXP() = 0;

};
