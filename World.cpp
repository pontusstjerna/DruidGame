#include "World.h"
#include <stdio.h>

World::World()
{
	char* sheets[2] = { "data/spritesheets/player_human.png", "data/spritesheets/player_cat.png" };

	activePlayer = new Player(100, 0, sheets);
	activeMap = new Map("none", "map1", activePlayer);
}

World::World(char* savedGame)
{
	
}

World::~World()
{
	delete activeMap;
}

void World::Update(float dTime)
{
	CollideCharacters(dTime);
	activeMap->Update(dTime);

}

//void SaveGame(char* saveName);

Player* World::GetPlayer()
{
	return activePlayer;
}

Model* World::GetMap()
{
	return activeMap;
}

Character* World::GetClosestCharacter(Character* character)
{
	Character* closest = activeMap->GetCharacters()[0];

	//If character is player
	if(character == closest)
		closest = activeMap->GetCharacters()[1];

	//Adjust x to be approx at mouth
	float x = character->GetX();
	if (character->GetDir() == Character::RIGHT)
		x += character->GetWidth();
		
	for (int i = 0; i < activeMap->GetNumberofObjects(); i++)
	{
		int dist = 0;
		Character* current = activeMap->GetCharacters()[i];
		if (current != character && current->Distance(x, character->GetY()) < closest->Distance(x, character->GetY()))
		{
			closest = current;
		}
	}

	return closest;
}

void World::CollideCharacters(float dTime)
{
	for (int i = 0; i < activeMap->GetNumberofObjects(); i++)
	{
		CollideCharacter(activeMap->GetCharacters()[i], dTime);
	}
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
	for (int i = 0; i < activeMap->GetNumberofBlocks(); i++)
	{
		//Nexts
		int bLeft = activeMap->GetBlocks()[i]->GetX();
		int bRight = activeMap->GetBlocks()[i]->GetX() + activeMap->GetBlocks()[i]->GetWidth();
		int bTop = activeMap->GetBlocks()[i]->GetY();
		int bBottom = activeMap->GetBlocks()[i]->GetY() + activeMap->GetBlocks()[i]->GetHeight();

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