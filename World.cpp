#include "World.h"

World::World()
{
	ActiveMap = new Map("none", "map1");
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
	
}

//void SaveGame(char* saveName);

//Player* World::GetPlayer()
//{
//	
//}

Map* World::GetMap()
{
	return ActiveMap;
}