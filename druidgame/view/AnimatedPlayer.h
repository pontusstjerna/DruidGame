#pragma once
#include "../model/GameObject.h"

class AnimatedPlayer : public GameObject
{
	public:
		virtual int getStamina() = 0;
		virtual int getMaxStamina() = 0;
		virtual int getLevel() = 0;
		virtual int getXP() = 0;
    
        // From GameObject.h
        /*virtual void update(float dTime) = 0;
        virtual char const* getName() = 0;
        virtual int getX() = 0;
        virtual int getY() = 0;
        virtual int getState() = 0;
        virtual int getDir() = 0;
        virtual int getWidth() = 0;
        virtual int getHeight() = 0;
        virtual float getHealth() = 0;
        virtual int getMaxHealth() = 0;*/
};
