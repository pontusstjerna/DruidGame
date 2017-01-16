#include "GUI.h"

GUI::GUI(AnimatedPlayer* player, int nObjects, AnimatedObject** objects) : Player(player), NumObjects(nObjects)
{
	Objects = new AnimatedObject*[nObjects];
	for (int i = 0; i < nObjects; i++)
	{
		Objects[i] = objects[i];
	}
}

GUI::~GUI()
{
	delete Objects;
}

int GUI::LoadGUI(SDL_Texture* background)
{
	Background = background;
	if (Background == NULL)
		return -1;

	return 0;
}