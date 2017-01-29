#pragma once
#include "AnimatedObject.h"

class AnimatedObjectView
{
	public:
		bool insideView = true;

		AnimatedObjectView(AnimatedObject* obj, int nFrames);
		void IncrementFrames();
		int GetFrame();
		int GetNumFrames();
		bool GetStateChanged();
		AnimatedObject* GetObject();

	private:
		int frame = 0;
		int nFrames = 0;
		bool stateChanged = false;
		int lastState = -1;
		int lastDir = -1;
		AnimatedObject* animatedObject;
};