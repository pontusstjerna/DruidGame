#include "World.h"
#include <stdio.h>
#include "../util/Geometry.h"

World::World()
{
	activePlayer = new Player(100, 0);
	activeMap = new Map("map1", activePlayer);
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
	interactObjects(dTime);
	activeMap->Update(dTime);

}

//void SaveGame(char* saveName);

Player* World::getPlayer()
{
	return activePlayer;
}

Model* World::getMap()
{
	return activeMap;
}

Character* World::getClosestCharacter(Character* character)
{
	Character* closest = activeMap->GetCharacters()[0];

	//If character is player
	if(character == closest)
		closest = activeMap->GetCharacters()[1];

	//Adjust x to be approx at mouth
	float x = character->getX();
	if (character->getDir() == Character::RIGHT)
		x += character->getWidth();
		
	for (int i = 0; i < activeMap->GetNumberofObjects(); i++)
	{
		int dist = 0;
		Character* current = activeMap->GetCharacters()[i];
		if (current != character && current->Distance(x, character->getY()) < closest->Distance(x, character->getY()))
		{
			closest = current;
		}
	}

	return closest;
}

void World::interactObjects(float dTime) {
    Character** characters = activeMap->GetCharacters();
    
	for (int i = 0; i < activeMap->GetNumberofObjects(); i++) {
		collideCharacter(characters[i], dTime);
        
        if (i != 0) { // Don't interact with yourself
            interactCharacters(activePlayer, characters[i]);
        }
        
        /*for (int j = 0; j < activeMap->GetNumberofObjects(); j++) {
            if (j != i) { // Don't interact with yourself
                interactCharacters(characters[i], characters[j]);
            }
        }*/
	}
}

void World::interactCharacters(Character* a, Character* b) {
    if (a->getMeleeWeapon() != NULL) {
        float dist = Geometry::distance(a->getX(), a->getY(), b->getX(), b->getY());
        b->Damage(a->getMeleeWeapon()->getDoneDmg(dist));
    }
}

void World::collideCharacter(Character* object, float dTime) {
	int pLeft = object->getX();
	int pRight = object->getX() + object->getWidth();
	int pTop = object->getY();
	int pBottom = object->getY() + object->getHeight() + object->GetFallingVel()*dTime;

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
