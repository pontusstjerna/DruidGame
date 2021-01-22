#include "GameView.h"
#include "TextureSizes.h"

using namespace std;

GameView::GameView(int winWidth, int winHeight, Model *map, AnimatedPlayer *player, TextureHandler *textureHandler) : winWidth(winWidth), winHeight(winHeight), activeMap(map), player(player), textureHandler(textureHandler)
{
	objects = new AnimatedObjectView *[map->GetNumberofObjects()];
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

void GameView::DrawBackground(SDL_Renderer *renderer, SDL_Texture *background, string name, float scale)
{
	int totWidth = 0;

	Rect sourceRect = TEXTURE_SIZES.at(name);

	float backgroundScale = 3.0f;
	int bgWidth = sourceRect.width * backgroundScale;
	int bgHeight = sourceRect.height * backgroundScale;
	while (totWidth < winWidth + 200)
	{
		int x = (int)((-player->getX() / 4) * backgroundScale) % bgWidth; // +WinWidth / 2;

		SDL_Rect sRect = {0, 0, sourceRect.width, sourceRect.height};
		SDL_Rect dRect = {x + totWidth, 0, bgWidth, winHeight};
		SDL_RenderCopy(renderer, background, &sRect, &dRect);

		totWidth += bgWidth;
	}
}

void GameView::DrawBlocks(SDL_Renderer *renderer, float scale)
{
	for (int i = 0; i < activeMap->getNumberBlocks(); i++)
	{
		//TODO: Check if inside view rect
		if (IsInsideView(activeMap->getBlocks()[i], scale))
			DrawBlock(activeMap->getBlocks()[i], renderer, scale);
	}
}

void GameView::DrawBlock(Block *block, SDL_Renderer *renderer, float scale)
{
	int x = (int)((block->getX() - objects[0]->GetObject()->getX() - (block->getWidth() / 2.0f)) * scale) + winWidth / 2;
	int y = (int)((block->getY() - objects[0]->GetObject()->getY() - (block->getHeight() / 2.0f)) * scale) + winHeight / 2;
	int h = block->getHeight();
	int mh = block->MIN_HEIGHT;

	//Top row
	DrawBlockRow(block, renderer, top, x, y, scale);

	if (h > mh)
	{
		//Middle vertical
		for (int i = mh; i < h - mh; i += mh)
		{
			DrawBlockRow(block, renderer, middle, x, y + (int)(i * scale), scale);
		}

		//Bottom
		DrawBlockRow(block, renderer, bottom, x, y + (int)((h - mh) * scale), scale);
	}
}

void GameView::DrawBlockRow(Block *block, SDL_Renderer *renderer, VerticalPos pos, int x, int y, float scale)
{

	int w = block->getWidth();
	int h = block->getHeight();
	int mw = block->MIN_WIDTH;
	int mh = block->MIN_HEIGHT;

	Rect sourceRect = TEXTURE_SIZES.at(block->getName());
	int sw = sourceRect.width;
	int sh = sourceRect.height;

	SDL_Texture *texture = textureHandler->getTexture(block->getName());

	if (w > 1 * mw)
	{
		//Draw top left
		SDL_Rect sRect = {0, pos * sh, sw, sh};
		SDL_Rect dRect = {x, y, (int)(mw * scale), (int)(mh * scale)};
		SDL_RenderCopy(renderer, texture, &sRect, &dRect);
	}

	//Middle blocks
	if (w > 2 * mw)
	{
		//Repeat middle texture for every width bigger than 2.
		for (int i = mw; i < w - mw; i += mw)
		{
			SDL_Rect sRect = {sw, pos * sh, sw, sh};
			SDL_Rect dRect = {x + (int)(i * scale), y, (int)(mw * scale), (int)(mh * scale)};
			SDL_RenderCopy(renderer, texture, &sRect, &dRect);
		}
	}

	//Top right, always paint
	SDL_Rect sRect = {sw * 2, pos * sh, sw, sh};
	SDL_Rect dRect = {x + (int)((w - mw) * scale), y, (int)(mw * scale), (int)(mh * scale)};
	SDL_RenderCopy(renderer, texture, &sRect, &dRect);
}

void GameView::DrawPlayer(SDL_Renderer *renderer, float scale)
{
	Rect sourceRect = TEXTURE_SIZES.at(player->getName());
	int sw = sourceRect.width;
	int sh = sourceRect.height;
	float w = player->getWidth();
	float h = player->getHeight();

	SDL_Texture *texture = textureHandler->getTexture(player->getName());

	//The State*height*2 is for frame index, frame height and 2 for number of directions
	SDL_Rect sRect = {objects[0]->GetFrame() * sw, player->getState() * sh * 2 + player->getDir() * sh, sw, sh};
	SDL_Rect dRect = {winWidth / 2 - (int)(w / 2.0f * scale), winHeight / 2 - (int)(h / 2.0f * scale), (int)(w * scale), (int)(h * scale)};
	SDL_RenderCopy(renderer, texture, &sRect, &dRect);
}

void GameView::DrawAnimatedObjects(SDL_Renderer *renderer, float scale)
{
	for (int i = 1; i < activeMap->GetNumberofObjects(); i++)
	{
		AnimatedObjectView *obj = objects[i];
		if (obj->insideView)
			DrawAnimatedObject(objects[i], renderer, scale);
	}
}

void GameView::DrawAnimatedObject(AnimatedObjectView *object, SDL_Renderer *renderer, float scale)
{
	Rect sourceRect = TEXTURE_SIZES.at(object->GetObject()->getName());

	int x = (int)((object->GetObject()->getX() - activeMap->GetObjects()[0]->getX()) * scale) + winWidth / 2;
	int y = (int)((object->GetObject()->getY() - activeMap->GetObjects()[0]->getY()) * scale) + winHeight / 2;
	int w = sourceRect.width;
	int h = sourceRect.height;

	//The State*height*2 is for frame index, frame height and 2 for number of directions
	SDL_Rect sRect = {object->GetFrame() * w, object->GetObject()->getState() * h * 2 + object->GetObject()->getDir() * h, w, h};

	SDL_Texture *texture = textureHandler->getTexture(object->GetObject()->getName());
	SDL_Rect dRect = {x, y, (int)(w * scale), (int)(h * scale)};
	SDL_RenderCopy(renderer, texture, &sRect, &dRect);

	//If it has health, otherwise it's either dead or for example grass
	if (object->GetObject()->getHealth() > 0)
	{
		//Draw health bar bg
		SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
		const int barHeight = (int)(scale * 2);
		SDL_Rect hpBar = {x, y - barHeight, (int)(w * scale), barHeight};
		SDL_RenderFillRect(renderer, &hpBar);

		//Draw health bar fg
		SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
		hpBar = {x, y - barHeight, (int)(w * scale * (object->GetObject()->getHealth() / object->GetObject()->getMaxHealth())), barHeight};
		SDL_RenderFillRect(renderer, &hpBar);
	}
}

bool GameView::IsInsideView(Block *block, float scale)
{
	int x = (int)((block->getX() - player->getX()) * scale) + winWidth / 2;
	int y = (int)((block->getY() - player->getY()) * scale) + winHeight / 2;
	int w = (int)(block->getWidth() * scale);
	int h = (int)(block->getHeight() * scale);
	// return x + w > 0 && x < winWidth && y + h > 0 && y < winHeight;
	return true;
}

void GameView::UpdateActiveObjects(float scale)
{
	for (int i = 1; i < activeMap->GetNumberofObjects(); i++)
	{
		if (IsInsideView(objects[i]->GetObject()->getX(), objects[i]->GetObject()->getY(), (int)objects[i]->GetObject()->getWidth(), (int)objects[i]->GetObject()->getHeight(), scale))
			objects[i]->insideView = true;
		else
			objects[i]->insideView = false;
	}
}

bool GameView::IsInsideView(float tx, float ty, float tw, float th, float scale)
{
	return true;
	int x = (int)((tx - player->getX()) * scale) + winWidth / 2;
	int y = (int)((ty - player->getY()) * scale) + winHeight / 2;
	int w = (int)(tw * scale);
	int h = (int)(th * scale);
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
