#pragma once
#include "GameObject.h"

class AnimatedObjectView
{
	public:
		bool insideView = true;

		AnimatedObjectView(GameObject* obj, int nFrames);
		void IncrementFrames();
		int GetFrame();
		int GetNumFrames();
		bool GetStateChanged();
		GameObject* GetObject();

	private:
		int frame = 0;
		int nFrames = 0;
		bool stateChanged = false;
		int lastState = -1;
		int lastDir = -1;
		GameObject* animatedObject;
};
