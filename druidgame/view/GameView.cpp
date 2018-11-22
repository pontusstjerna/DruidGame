#include "GameView.h"

GameView::GameView(int winWidth, int winHeight, Model* map, AnimatedPlayer* player, TextureHandler* textureHandler) :
    winWidth(winWidth), winHeight(winHeight), activeMap(map), player(player), textureHandler(textureHandler) {
	objects = new AnimatedObjectView*[map->GetNumberofObjects()];
	for (int i = 0; i < activeMap->GetNumberofObjects(); i++)
	{
		objects[i] = new AnimatedObjectView(activeMap->GetObjects()[i], NUMBEROF_FRAMES);
	}
}

GameView::~GameView()
{
	for (int i = 0; i < activeMap->GetNumberofObjects(); i++)
	{
		delete objects[i];
	}

	delete objects;
}

void GameView::DrawBackground(SDL_Renderer* renderer, SDL_Texture* background, float scale)
{
	int totWidth = 0;

	int bgWidth = 200 * scale;
	int bgHeight = 150 * scale;
	while (totWidth < winWidth + 200)
	{
		int x = (int)((-player->getX() / 4)*scale) % bgWidth;// +WinWidth / 2;

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
	int x = (int)((block->GetX() - objects[0]->GetObject()->getX())*scale) + winWidth / 2;
	int y = (int)((block->GetY() - objects[0]->GetObject()->getY())*scale) + winHeight / 2;
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
    
    SDL_Texture* texture = textureHandler->getTexture(block->getName())->getTexture();

	float zoom = 3;

	if (w > 1 * mw)
	{
		//Draw top left
		SDL_Rect sRect = { 0, pos*mh, mw, mh };
		SDL_Rect dRect = { x, y, (int)(mw * zoom), (int)(mh * zoom) };
		SDL_RenderCopy(renderer, texture, &sRect, &dRect);
	}

	//Middle blocks
	if (w > 2 * mw)
	{
		//Repeat middle texture for every width bigger than 2.
		for (int i = mw; i < w - mw; i += mw)
		{
			SDL_Rect sRect = { mw, pos*mh, mw, mh };
			SDL_Rect dRect = { x + (int)(i * zoom), y, (int)(mw * zoom), (int)(mh * zoom) };
			SDL_RenderCopy(renderer, texture, &sRect, &dRect);
		}
	}

	//Top right, always paint
	SDL_Rect sRect = { mw * 2, pos*mh, mw, mh };
	SDL_Rect dRect = { x + (int)((w - mw) * zoom), y, (int)(mw * zoom), (int)(mh * zoom) };
	SDL_RenderCopy(renderer, texture, &sRect, &dRect);
}

void GameView::DrawPlayer(SDL_Renderer* renderer, float scale)
{
	int x = player->getX();
	int y = player->getY();
	int w = player->getWidth();
	int h = player->getHeight();

	//The State*height*2 is for frame index, frame height and 2 for number of directions
	SDL_Rect sRect = { objects[0]->GetFrame()*w, player->getState()*h * 2 + player->getDir()*h , w, h };
	SDL_Rect dRect = { winWidth / 2, winHeight / 2, (int)(w * scale), (int)(h * scale) };
	SDL_RenderCopy(renderer, player->GetSpriteSheets()[player->GetActiveSpriteSheet()], &sRect, &dRect);
}

void GameView::DrawAnimatedObjects(SDL_Renderer* renderer, float scale)
{
	for (int i = 1; i < activeMap->GetNumberofObjects(); i++)
	{
		AnimatedObjectView* obj = objects[i];
		if (obj->insideView)
			DrawAnimatedObject(objects[i], renderer, scale);
	}
}

void GameView::DrawAnimatedObject(AnimatedObjectView* object, SDL_Renderer* renderer, float scale)
{
	int x = (int)((object->GetObject()->getX() - activeMap->GetObjects()[0]->getX())*scale) + winWidth / 2;
	int y = (int)((object->GetObject()->getY() - activeMap->GetObjects()[0]->getY())*scale) + winHeight / 2;
	int w = object->GetObject()->getWidth();
	int h = object->GetObject()->getHeight();

	//The State*height*2 is for frame index, frame height and 2 for number of directions
	SDL_Rect sRect = { object->GetFrame()*w, object->GetObject()->getState()*h * 2 + object->GetObject()->getDir()*h , w, h };
    
    SDL_Texture* texture = textureHandler->getTexture(object->GetObject()->getName())->getTexture();
	SDL_Rect dRect = { x, y, (int)(w*scale), (int)(h*scale) };
	SDL_RenderCopy(renderer, texture, &sRect, &dRect);

	//If it has health, otherwise it's either dead or for example grass
	if (object->GetObject()->getHealth() > 0)
	{
		//Draw health bar bg
		SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
		const int barHeight = (int)(scale * 2);
		SDL_Rect hpBar = { x, y - barHeight, (int)(w*scale) , barHeight };
		SDL_RenderFillRect(renderer, &hpBar);

		//Draw health bar fg
		SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
		hpBar = { x, y - barHeight, (int)(w*scale*(object->GetObject()->getHealth() / object->GetObject()->getMaxHealth())) , barHeight };
		SDL_RenderFillRect(renderer, &hpBar);
	}
}

bool GameView::IsInsideView(Block* block, float scale)
{
	int x = (int)((block->GetX() - player->getX())*scale) + winWidth / 2;
	int y = (int)((block->GetY() - player->getY())*scale) + winHeight / 2;
	int w = (int)(block->GetWidth()*scale);
	int h = (int)(block->GetHeight()*scale);
	return x + w > 0 && x < winWidth && y + h > 0 && y < winHeight;
}

void GameView::UpdateActiveObjects(float scale)
{
	for (int i = 1; i < activeMap->GetNumberofObjects(); i++)
	{
		SDL_Rect objRect = { objects[i]->GetObject()->getX(), objects[i]->GetObject()->getY(), objects[i]->GetObject()->getWidth(), objects[i]->GetObject()->getHeight() };
		if (IsInsideView(objRect, scale))
			objects[i]->insideView = true;
		else
			objects[i]->insideView = false;
	}
}

bool GameView::IsInsideView(SDL_Rect rect, float scale)
{
	int x = (int)((rect.x - player->getX())*scale) + winWidth / 2;
	int y = (int)((rect.y - player->getY())*scale) + winHeight / 2;
	int w = (int)(rect.w*scale);
	int h = (int)(rect.h*scale);
	return x + w > 0 && x < winWidth && y + h > 0 && y < winHeight;
}

float frameCounter = 0;
void GameView::IncrementFrames(float dTime)
{
	frameCounter += dTime;

	if (frameCounter > STD_UPDATE_INTERVAL)
	{
		for (int i = 0; i < activeMap->GetNumberofObjects(); i++)
		{
			objects[i]->IncrementFrames();
		}
		frameCounter = 0;
	}
}
