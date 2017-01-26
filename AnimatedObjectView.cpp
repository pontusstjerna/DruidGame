#include "AnimatedObjectView.h"

AnimatedObjectView::AnimatedObjectView(AnimatedObject* obj) : animatedObject(obj) {}

void AnimatedObjectView::IncrementFrames()
{

}

int AnimatedObjectView::GetFrame()
{
	return frame;
}

AnimatedObject* GetObject();