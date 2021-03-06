#include "GUI.h"

GUI::GUI(AnimatedPlayer* player, int nObjects, GameObject** objects) : Player(player), NumObjects(nObjects)
{
	Objects = new GameObject*[nObjects];
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
	DrawHealth(renderer);
	DrawStamina(renderer);
}

void GUI::DrawBackground(SDL_Renderer* renderer)
{
	SDL_Rect sRect = { 0, 0, BG_WIDTH, BG_HEIGHT };
	SDL_Rect dRect = { 0, 0, WinWidth, WinHeight };
	SDL_RenderCopy(renderer, Textures[BACKGROUND], &sRect, &dRect);
}

void GUI::DrawHealth(SDL_Renderer* renderer)
{
	float healthPercent = (float)Player->getHealth() / Player->getMaxHealth();
	SDL_Rect sRect = { 0, 0, (int)(PLAYER_BAR_WIDTH*healthPercent), PLAYER_BAR_HEIGHT };
	SDL_Rect dRect = { (int)(25*GetScaleX()), (int)(5*GetScaleY()), (int)(PLAYER_BAR_WIDTH*healthPercent*GetScaleX()), (int)(PLAYER_BAR_HEIGHT*GetScaleY()) };
	SDL_RenderCopy(renderer, Textures[HEALTH_BAR], &sRect, &dRect);
}

void GUI::DrawStamina(SDL_Renderer* renderer)
{
	float staPercent = (float)Player->getStamina() / Player->getMaxStamina();
	SDL_Rect sRect = { 0, 0, (int)(PLAYER_BAR_WIDTH*staPercent), PLAYER_BAR_HEIGHT };
	SDL_Rect dRect = { (int)(25 * GetScaleX()), (int)(25 * GetScaleY()), (int)(PLAYER_BAR_WIDTH*staPercent*GetScaleX()), (int)(PLAYER_BAR_HEIGHT*GetScaleY()) };
	SDL_RenderCopy(renderer, Textures[STA_BAR], &sRect, &dRect);
}

float GUI::GetScaleX()
{
	return (float)WinWidth / BG_WIDTH;
}

float GUI::GetScaleY()
{
	return (float)WinHeight / BG_HEIGHT;
}
