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

int GUI::LoadGUI(SDL_Texture** textures, int win_width, int win_height)
{
	WinWidth = win_width;
	WinHeight = win_height;

	Textures = new SDL_Texture*[nTextures];
	for (int i = 0; i < nTextures; i++)
	{
		if (textures[i] == NULL)
			return -1;

		Textures[i] = textures[i];
	}

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
	SDL_RenderCopy(renderer, Textures[BACKGROUND], &sRect, &dRect);
}

void GUI::DrawHealth(SDL_Renderer* renderer)
{
	SDL_Rect sRect = { 0, 0, 49, BG_HEIGHT };
	SDL_Rect dRect = { 0, 0, WinWidth, WinHeight };
	SDL_RenderCopy(renderer, Textures[BACKGROUND], &sRect, &dRect);
}

float GUI::GetScaleX()
{
	return (float)WinWidth / BG_WIDTH;
}

float GUI::GetScaleY()
{
	return (float)WinHeight / BG_HEIGHT;
}