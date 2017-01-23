#include "World.h"
#include <stdio.h>

World::World()
{
	char* sheets[2] = { "data/spritesheets/player_human.png", "data/spritesheets/player_cat.png" };

	ActivePlayer = new Player(100, 0, sheets);
	ActiveMap = new Map("none", "map1", ActivePlayer);
}

World::World(char* savedGame)
{
	
}

World::~World()
{
	delete ActiveMap;
}

void World::Update(float dTime)
{
	CollideCharacters(dTime);
	ActiveMap->Update(dTime);

}

//void SaveGame(char* saveName);

Player* World::GetPlayer()
{
	return ActivePlayer;
}

Map* World::GetMap()
{
	return ActiveMap;
}

void World::CollideCharacters(float dTime)
{

}

void World::CollideCharacter(Character* object, float dTime)
{
	int pLeft = object->GetX();
	int pRight = object->GetX() + object->GetWidth();
	int pTop = object->GetY();
	int pBottom = object->GetY() + object->GetHeight() + object->GetFallingVel()*dTime;

	bool left = false;
	bool right = false;
	bool top = false;
	bool bottom = false;

	//printf("LS: %i\n", pLeft);

	//Loop through all blocks
	for (int i = 0; i < ActiveMap->GetNumberofBlocks(); i++)
	{
		//Nexts
		int bLeft = ActiveMap->GetBlocks()[i]->GetX();
		int bRight = ActiveMap->GetBlocks()[i]->GetX() + ActiveMap->GetBlocks()[i]->GetWidth();
		int bTop = ActiveMap->GetBlocks()[i]->GetY();
		int bBottom = ActiveMap->GetBlocks()[i]->GetY() + ActiveMap->GetBlocks()[i]->GetHeight();

		bool betweenVertical = bTop < pBottom && bBottom > pTop;
		bool betweenHorizontal = bLeft < pRight && bRight > pLeft;

		if(!left)
			left = (pLeft <= bRight && pRight >= bRight && betweenVertical);

		if(!right)
			right = (pRight >= bLeft && pLeft <= bLeft && betweenVertical);

		if (right)
			int x = 5;

		if(!top)
			top = (pTop <= bBottom && pBottom >= bBottom && betweenHorizontal);

		if (!bottom)
			bottom = (pBottom >= bTop && pTop <= bTop && betweenHorizontal);

	}

	object->Collide(Character::LEFT, left);
	object->Collide(Character::RIGHT, right);
	object->Collide(Character::TOP, top);
	object->Collide(Character::BOTTOM, bottom);

}