#include "World.h"
#include <stdio.h>
#include "../util/Geometry.h"
#include <cmath>

World::World()
{
	activePlayer = new Player(100, 0);
	activeMap = new Map("map1", activePlayer);
}

World::World(char* savedGame) {
	
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
            interactPlayerCharacter(activePlayer, characters[i]);
        }
	}
}

void World::interactPlayerCharacter(Character* player, Character* character) {
    if (player->getMeleeWeapon() != NULL) {
        int dir = player->getDir() == Character::LEFT ? -1 : 1;
        float playerX = player->getX() + dir * (player->getWidth() / 2);
        float dist = Geometry::distance(playerX, player->getY(), character->getX(), character->getY());
        character->damage(player->getMeleeWeapon()->getDoneDmg(dist));
    }
}

void World::collideCharacter(Character* object, float dTime) {
	int pLeft = object->getX();
	int pRight = object->getX() + object->getWidth();
	int pTop = object->getY() - object->getYVel() * dTime;
    int pBottom = object->getY() + object->getHeight() + object->getYVel() * dTime;

	//printf("LS: %i\n", pLeft);
    bool hasCollided = false;
    bool collisions[4];

	//Loop through all blocks
	for (int i = 0; i < activeMap->getNumberBlocks() /*&& !intersection*/; i++) {
        Block* block = activeMap->getBlocks()[i];
        
		//Nexts
		int bLeft = block->getX();
		int bRight = block->getX() + block->getWidth();
		int bTop = block->getY();
		int bBottom = block->getY() + block->getHeight();

		bool betweenVertical = bTop < pBottom && bBottom > pTop;
		bool betweenHorizontal = bLeft < pRight && bRight > pLeft;
        
        collisions[Character::LEFT] = pLeft <= bRight && pRight >= bRight && betweenVertical;
        collisions[Character::RIGHT] = pRight >= bLeft && pLeft <= bLeft && betweenVertical;
        collisions[Character::TOP] = pTop <= bBottom && pBottom >= bBottom && betweenHorizontal;
        collisions[Character::BOTTOM] = pBottom >= bTop && pTop <= bTop && betweenHorizontal;
        
        bool intersection = collisions[0] || collisions[1] || collisions[2] || collisions[3];
        hasCollided = intersection || hasCollided;
        
        if (intersection) {
            resolveCollision(object, block, collisions);
        }
	}
    
    if (!hasCollided) {
        object->clearCollisions();
    }
}

void World::resolveCollision(Character* object, Block* block, bool collisions[4]) {
    float objCenterX = object->getX() + object->getWidth() / 2;
    float objCenterY = object->getY() + ((object->getHeight()) / 2);
    
    float blockCenterX = block->getX() + block->getWidth() / 2;
    float blockCenterY = block->getY() + block->getHeight() / 2;
    
    float aw = (object->getWidth() + block->getWidth()) / 2;
    float ah = (object->getHeight() + block->getHeight()) / 2;
    
    float vectorX = objCenterX - blockCenterX;
    float vectorY = objCenterY - blockCenterY;
    
    if (abs(vectorX) > aw || abs(vectorY) > ah) {
        return;
    }
    
    // Is the vector y longer than vector x?
    if (abs(vectorY / block->getHeight()) > abs(vectorX / block->getWidth())) { // Collision top or bottom
        if (vectorY > 0) { // VectorY pointing down
            object->collide(collisions, block->getY() + block->getHeight() + 1);
        } else { // VectorY pointing up
            object->collide(collisions, block->getY() - object->getHeight());
        }
    } else {
        if (vectorX > 0) { // VectorX pointing right
            object->collide(collisions, block->getX() + block->getWidth() + 1);
        } else { // VectorX pointing left
            object->collide(collisions, block->getX() - object->getWidth());
        }
    }
}
