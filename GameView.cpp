#include "GameView.h"

GameView::GameView(int winWidth, int winHeight, Map* map, AnimatedPlayer* player) : WinWidth(winWidth), WinHeight(winHeight), ActiveMap(map), Player(player)
{
	
}

void GameView::DrawBackground(SDL_Renderer* renderer, SDL_Texture* background, float scale)
{
	int totWidth = 0;

	int bgWidth = 200 * scale;
	int bgHeight = 150 * scale;
	while (totWidth < WinWidth + 200)
	{
		int x = (int)((-Player->GetX() / 4)*scale) % bgWidth;// +WinWidth / 2;

		SDL_Rect sRect = { 0, 0, bgWidth, bgHeight };
		SDL_Rect dRect = { x + totWidth, 0, bgWidth, WinHeight };
		SDL_RenderCopy(renderer, background, &sRect, &dRect);

		totWidth += bgWidth;
	}
}

void GameView::DrawBlocks(SDL_Renderer* renderer, float scale)
{
	for (int i = 0; i < ActiveMap->GetNumberofBlocks(); i++)
	{
		//TODO: Check if inside view rect
		if (IsInsideView(ActiveMap->GetBlocks()[i], scale))
			DrawBlock(ActiveMap->GetBlocks()[i], renderer, scale);
	}
}

void GameView::DrawBlock(Block* block, SDL_Renderer* renderer, float scale)
{
	int x = (int)((block->GetX() - ActiveMap->GetObjects()[0]->GetX())*scale) + WinWidth / 2;
	int y = (int)((block->GetY() - ActiveMap->GetObjects()[0]->GetY())*scale) + WinHeight / 2;
	int h = block->GetHeight();
	int mh = block->MIN_HEIGHT;

	//Top row
	DrawBlockRow(block, renderer, top, x, y, scale);

	if (h > mh)
	{
		//Middle vertical
		for (int i = mh; i < h - mh; i += mh)
		{
			DrawBlockRow(block, renderer, middle, x, y + (int)(i*scale), scale);
		}

		//Bottom
		DrawBlockRow(block, renderer, bottom, x, y + (int)((h - mh)*scale), scale);
	}
}

void GameView::DrawBlockRow(Block* block, SDL_Renderer* renderer, VerticalPos pos, int x, int y, float scale)
{

	
	int w = block->GetWidth();// -player->GetY();
	int h = block->GetHeight();
	int mw = block->MIN_WIDTH;
	int mh = block->MIN_HEIGHT;

	float zoom = 3;

	if (w > 1 * mw)
	{
		//Draw top left
		SDL_Rect sRect = { 0, pos*mh, mw, mh };
		SDL_Rect dRect = { x, y, (int)(mw*zoom), (int)mh*zoom };
		SDL_RenderCopy(renderer, block->GetTexture(), &sRect, &dRect);
	}

	//Middle blocks
	if (w > 2 * mw)
	{
		//Repeat middle texture for every width bigger than 2.
		for (int i = mw; i < w - mw; i += mw)
		{
			SDL_Rect sRect = { mw, pos*mh, mw, mh };
			SDL_Rect dRect = { x + (int)(i*zoom), y, (int)(mw*zoom), (int)mh*zoom };
			SDL_RenderCopy(renderer, block->GetTexture(), &sRect, &dRect);
		}
	}

	//Top right, always paint
	SDL_Rect sRect = { mw * 2, pos*mh, mw, mh };
	SDL_Rect dRect = { x + (int)((w - mw)*zoom), y, (int)(mw*zoom), (int)mh*zoom };
	SDL_RenderCopy(renderer, block->GetTexture(), &sRect, &dRect);
}

void GameView::DrawPlayer(SDL_Renderer* renderer, float scale)
{
	int x = Player->GetX();
	int y = Player->GetY();
	int w = Player->GetWidth();
	int h = Player->GetHeight();

	//The State*height*2 is for frame index, frame height and 2 for number of directions
	SDL_Rect sRect = { Frame*w, Player->GetState()*h * 2 + Player->GetDir()*h , w, h };
	SDL_Rect dRect = { WinWidth / 2, WinHeight / 2, (int)(w*scale), (int)(h*scale) };
	SDL_RenderCopy(renderer, Player->GetSpriteSheets()[Player->GetActiveSpriteSheet()], &sRect, &dRect);

}

void GameView::DrawAnimatedObjects(SDL_Renderer* renderer, float scale)
{
	for (int i = 1; i < ActiveMap->GetNumberofObjects(); i++)
	{
		//TODO: Check if inside view rect
		//if (IsInsideView(ActiveMap->GetBlocks()[i], scale))
			DrawAnimatedObject(ActiveMap->GetObjects()[i], renderer, scale);
	}
}

void GameView::DrawAnimatedObject(AnimatedObject* object, SDL_Renderer* renderer, float scale)
{
	int x = (int)((object->GetX() - ActiveMap->GetObjects()[0]->GetX())*scale) + WinWidth / 2;
	int y = (int)((object->GetY() - ActiveMap->GetObjects()[0]->GetY())*scale) + WinHeight / 2;
	int w = object->GetWidth();
	int h = object->GetHeight();

	//The State*height*2 is for frame index, frame height and 2 for number of directions
	SDL_Rect sRect = { Frame*w, object->GetState()*h * 2 + object->GetDir()*h , w, h };
	SDL_Rect dRect = { x, y, (int)(w*scale), (int)(h*scale) };
	SDL_RenderCopy(renderer, object->GetSpriteSheet(), &sRect, &dRect);
}

bool GameView::IsInsideView(Block* block, float scale)
{
	int x = (int)((block->GetX() - Player->GetX())*scale) + WinWidth / 2;
	int y = (int)((block->GetY() - ActiveMap->GetObjects()[0]->GetY())*scale) + WinHeight / 2;
	int w = (int)(block->GetWidth()*scale);
	int h = (int)(block->GetHeight()*scale);
	return x + w > 0 && x < WinWidth && y + h > 0 && y < WinHeight;
}

float FrameCounter = 0;
void GameView::IncrementFrames(float dTime)
{
	FrameCounter += dTime;

	if (FrameCounter > STD_UPDATE_INTERVAL)
	{
		Frame = (Frame + 1) % NUMBEROF_FRAMES;
		FrameCounter = 0;
	}
}