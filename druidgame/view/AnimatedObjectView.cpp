#include "AnimatedObjectView.h"

AnimatedObjectView::AnimatedObjectView(GameObject* obj, int nFrames) : animatedObject(obj), nFrames(nFrames) {}

void AnimatedObjectView::IncrementFrames()
{
	if (animatedObject->getState() != GameObject::DEAD || frame < nFrames-1)
	{
		frame = (frame + 1) % nFrames;
	}
	else
	{
		//Only display last frame
		frame = nFrames - 1;
		return;
	}
	
	if (lastState != animatedObject->getState() || lastDir != animatedObject->getDir())
	{
		stateChanged = true;
		frame = 0;
	}
	else
		stateChanged = false;

	lastDir = animatedObject->getDir();
	lastState = animatedObject->getState();
}

int AnimatedObjectView::GetFrame()
{
	return frame;
}

GameObject* AnimatedObjectView::GetObject()
{
	return animatedObject;
}

int AnimatedObjectView::GetNumFrames()
{
	return nFrames;
}

bool AnimatedObjectView::GetStateChanged()
{
	return stateChanged;
}
