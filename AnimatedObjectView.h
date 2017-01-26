#pragma once
#include "AnimatedObject.h"

class AnimatedObjectView
{
	public:
		bool insideView = true;

		AnimatedObjectView(AnimatedObject* obj);
		void IncrementFrames();
		int GetFrame();
		AnimatedObject* GetObject();

	private:
		int frame = 0;
		AnimatedObject* animatedObject;
};