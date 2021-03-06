#pragma once
#include "../model/GameObject.h"
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
		Character* getClosestCharacter(Character* character);

		//void SaveGame(char* saveName);

		Player* getPlayer();
		Model* getMap(); 

	private:
		Player* activePlayer;
		Map* activeMap;

		void interactObjects(float dTime);
        void resolveCollision(Character* object, Block* block, bool collisions[4]);
		void collideCharacter(Character* object, float dTime);
        void interactPlayerCharacter(Character* a, Character* b);

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
