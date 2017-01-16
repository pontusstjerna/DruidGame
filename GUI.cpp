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

int GUI::LoadGUI(SDL_Texture* background, int win_width, int win_height)
{
	WinWidth = win_width;
	WinHeight = win_height;

	Background = background;
	if (Background == NULL)
		return -1;

	return 0;
}

void GUI::Draw(SDL_Renderer* renderer)
{
	DrawBackground(renderer);

}

void GUI::DrawBackground(SDL_Renderer* renderer)
{
	SDL_Rect sRect = { 0, 0, BG_WIDTH, BG_HEIGHT };
	SDL_Rect dRect = { 0, 0, WinWidth, WinHeight };
	SDL_RenderCopy(renderer, Background, &sRect, &dRect);
}