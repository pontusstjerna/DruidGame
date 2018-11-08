#include "AnimatedObjectView.h"

AnimatedObjectView::AnimatedObjectView(AnimatedObject* obj, int nFrames) : animatedObject(obj), nFrames(nFrames) {}

void AnimatedObjectView::IncrementFrames()
{
	if (animatedObject->GetState() != AnimatedObject::DEAD || frame < nFrames-1)
	{
		frame = (frame + 1) % nFrames;
	}
	else
	{
		//Only display last frame
		frame = nFrames - 1;
		return;
	}
	
	if (lastState != animatedObject->GetState() || lastDir != animatedObject->GetDir())
	{
		stateChanged = true;
		frame = 0;
	}
	else
		stateChanged = false;

	lastDir = animatedObject->GetDir();
	lastState = animatedObject->GetState();
}

int AnimatedObjectView::GetFrame()
{
	return frame;
}

AnimatedObject* AnimatedObjectView::GetObject()
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