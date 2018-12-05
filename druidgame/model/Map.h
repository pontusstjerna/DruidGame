#pragma once
#include "Block.h"
#include "../model/GameObject.h"
#include "AnimatedPlayer.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Model.h"

class Map : public Model
{
	public:
		Map(char* name, Player* player);
		~Map();

		void Update(float dTime);

		char* GetBackground();

		int getNumberBlocks();
		Block** getBlocks();
		int GetNumberofObjects();
		GameObject** GetObjects();
		Character** GetCharacters();
        AnimatedPlayer* getPlayer();

	private:
		char* name;
		char* background;
		int NumberOfBlocks;
		Block** blocks;
		int nObjects;
		Character** characters;
        Player* player;
		//Enemy** Enemies;
		//Enemies
		
};
