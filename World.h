#pragma once
#include "AnimatedObject.h"
#include "Map.h"
#include "Player.h"
#include "Character.h"

class World
{
	public:
		World();
		World(char* savedGame);
		~World();

		void Update(float dTime);

		//void SaveGame(char* saveName);

		Player* GetPlayer();
		Model* GetMap(); 

	private:
		Player* activePlayer;
		Map* activeMap;

		void CollideCharacters(float dTime);
		void CollideCharacter(Character* object, float dTime);

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