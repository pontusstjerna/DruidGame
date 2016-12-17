#pragma once
#include "AnimatedObject.h"
#include "Level.h"
#include "Player.h"

class World
{
	public:
		World();
		World(char* savedGame);
		~World();

		void Update(float dTime);

		//void SaveGame(char* saveName);

		Player* GetPlayer();
		AnimatedObject* GetAnimatedObjects();
		Level* GetLevel(); 

		/*
		{
		"LevelName" : "Level1",
		"Objects" : [
		{
		"ObjectID" : 1,
		"Model" : "Wall",
		"X" : "20",
		"Y" : "0",
		"Z" : "0"
		}
		{
		"ObjectID" : 2,
		"Model" : "Wall",
		"X" : "15",
		"Y" : "0",
		"Z" : "0"
		}
		]
		}
		*/
};