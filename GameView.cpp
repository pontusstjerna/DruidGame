#include "GameView.h"

GameView::GameView()

void GameView::DrawBackground(SDL_Renderer* renderer, float scale)
{
	int totWidth = 0;

	int bgWidth = 200 * scale;
	int bgHeight = 150 * scale;
	while (totWidth < WINDOW_WIDTH + 200)
	{
		int x = (int)((-Player->GetX() / 4)*scale) % bgWidth;// +WINDOW_WIDTH / 2;

		SDL_Rect sRect = { 0, 0, bgWidth, bgHeight };
		SDL_Rect dRect = { x + totWidth, 0, bgWidth, WINDOW_HEIGHT };
		SDL_RenderCopy(renderer, Background, &sRect, &dRect);

		totWidth += bgWidth;
	}
}

void GameView::DrawBlocks(SDL_Renderer* renderer, float scale)
{
	for (int i = 0; i < ActiveMap->GetNumberofBlocks(); i++)
	{
		SDL_Texture* texture;

		//TODO: Check if inside view rect
		if (IsInsideView(ActiveMap->GetBlocks()[i]))
			DrawBlock(ActiveMap->GetBlocks()[i], renderer);
	}
}

void View::DrawBlock(Block* block, SDL_Renderer* renderer)
{
	int y = (int)((block->GetY() - ActiveMap->GetObjects()[0]->GetY())*Scale) + WINDOW_HEIGHT / 2;
	int h = block->GetHeight();
	int mh = block->MIN_HEIGHT;

	//Top row
	DrawBlockRow(block, renderer, top, y);

	if (h > mh)
	{
		//Middle vertical
		for (int i = mh; i < h - mh; i += mh)
		{
			DrawBlockRow(block, renderer, middle, y + (int)(i*Scale));
		}

		//Bottom
		DrawBlockRow(block, renderer, bottom, y + (int)((h - mh)*Scale));
	}
}

void View::DrawBlockRow(Block* block, SDL_Renderer* renderer, VerticalPos pos, int y)
{

	int x = (int)((block->GetX() - ActiveMap->GetObjects()[0]->GetX())*Scale) + WINDOW_WIDTH / 2;
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

void View::DrawPlayer(SDL_Renderer* renderer)
{
	int x = Player->GetX();
	int y = Player->GetY();
	int w = Player->GetWidth();
	int h = Player->GetHeight();

	//The State*height*2 is for frame index, frame height and 2 for number of directions
	SDL_Rect sRect = { Frame*w, Player->GetState()*h * 2 + Player->GetDir()*h , w, h };
	SDL_Rect dRect = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, (int)(w*Scale), (int)(h*Scale) };
	SDL_RenderCopy(renderer, Player->GetSpriteSheets()[Player->GetActiveSpriteSheet()], &sRect, &dRect);

}