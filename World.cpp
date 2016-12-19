#include "World.h"

World::World()
{
	ActivePlayer = new Player(50, 50);
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
	ActiveMap->Update(dTime);
	ActivePlayer->MoveRight();
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