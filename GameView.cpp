#include "GameView.h"

GameView::GameView(int winWidth, int winHeight, Model* map, AnimatedPlayer* player) : winWidth(winWidth), winHeight(winHeight), activeMap(map), player(player)
{
	
}

void GameView::DrawBackground(SDL_Renderer* renderer, SDL_Texture* background, float scale)
{
	int totWidth = 0;

	int bgWidth = 200 * scale;
	int bgHeight = 150 * scale;
	while (totWidth < winWidth + 200)
	{
		int x = (int)((-player->GetX() / 4)*scale) % bgWidth;// +WinWidth / 2;

		SDL_Rect sRect = { 0, 0, bgWidth, bgHeight };
		SDL_Rect dRect = { x + totWidth, 0, bgWidth, winHeight };
		SDL_RenderCopy(renderer, background, &sRect, &dRect);

		totWidth += bgWidth;
	}
}

void GameView::DrawBlocks(SDL_Renderer* renderer, float scale)
{
	for (int i = 0; i < activeMap->GetNumberofBlocks(); i++)
	{
		//TODO: Check if inside view rect
		if (IsInsideView(activeMap->GetBlocks()[i], scale))
			DrawBlock(activeMap->GetBlocks()[i], renderer, scale);
	}
}

void GameView::DrawBlock(Block* block, SDL_Renderer* renderer, float scale)
{
	int x = (int)((block->GetX() - activeMap->GetObjects()[0]->GetX())*scale) + winWidth / 2;
	int y = (int)((block->GetY() - activeMap->GetObjects()[0]->GetY())*scale) + winHeight / 2;
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
	int x = player->GetX();
	int y = player->GetY();
	int w = player->GetWidth();
	int h = player->GetHeight();

	//The State*height*2 is for frame index, frame height and 2 for number of directions
	SDL_Rect sRect = { frame*w, player->GetState()*h * 2 + player->GetDir()*h , w, h };
	SDL_Rect dRect = { winWidth / 2, winHeight / 2, (int)(w*scale), (int)(h*scale) };
	SDL_RenderCopy(renderer, player->GetSpriteSheets()[player->GetActiveSpriteSheet()], &sRect, &dRect);

}

void GameView::DrawAnimatedObjects(SDL_Renderer* renderer, float scale)
{
	for (int i = 1; i < activeMap->GetNumberofObjects(); i++)
	{
		AnimatedObject* obj = activeMap->GetObjects()[i];
		if (obj->active)
			DrawAnimatedObject(activeMap->GetObjects()[i], renderer, scale);
	}
}

void GameView::DrawAnimatedObject(AnimatedObject* object, SDL_Renderer* renderer, float scale)
{
	int x = (int)((object->GetX() - activeMap->GetObjects()[0]->GetX())*scale) + winWidth / 2;
	int y = (int)((object->GetY() - activeMap->GetObjects()[0]->GetY())*scale) + winHeight / 2;
	int w = object->GetWidth();
	int h = object->GetHeight();

	//The State*height*2 is for frame index, frame height and 2 for number of directions
	SDL_Rect sRect = { frame*w, object->GetState()*h * 2 + object->GetDir()*h , w, h };
	SDL_Rect dRect = { x, y, (int)(w*scale), (int)(h*scale) };
	SDL_RenderCopy(renderer, object->GetSpriteSheet(), &sRect, &dRect);

	//Draw health bar bg
	const int barHeight = (int)(scale * 2);
	SDL_Rect hpBar = { x, y - barHeight, (int)(w*scale) , barHeight};
	SDL_RenderFillRect(renderer, &hpBar);
}

bool GameView::IsInsideView(Block* block, float scale)
{
	int x = (int)((block->GetX() - player->GetX())*scale) + winWidth / 2;
	int y = (int)((block->GetY() - player->GetY())*scale) + winHeight / 2;
	int w = (int)(block->GetWidth()*scale);
	int h = (int)(block->GetHeight()*scale);
	return x + w > 0 && x < winWidth && y + h > 0 && y < winHeight;
}

void GameView::UpdateActiveObjects(float scale)
{
	for (int i = 1; i < activeMap->GetNumberofObjects(); i++)
	{
		AnimatedObject* obj = activeMap->GetObjects()[i];
		SDL_Rect objRect = { obj->GetX(), obj->GetY(), obj->GetWidth(), obj->GetHeight() };
		if (IsInsideView(objRect, scale))
			obj->active = true;
		else
			obj->active = false;
	}
}

bool GameView::IsInsideView(SDL_Rect rect, float scale)
{
	int x = (int)((rect.x - player->GetX())*scale) + winWidth / 2;
	int y = (int)((rect.y - player->GetY())*scale) + winHeight / 2;
	int w = (int)(rect.w*scale);
	int h = (int)(rect.h*scale);
	return x + w > 0 && x < winWidth && y + h > 0 && y < winHeight;
}

float FrameCounter = 0;
void GameView::IncrementFrames(float dTime)
{
	FrameCounter += dTime;

	if (FrameCounter > STD_UPDATE_INTERVAL)
	{
		frame = (frame + 1) % NUMBEROF_FRAMES;
		FrameCounter = 0;
	}
}