#pragma once
#include "Block.h"
#include "AnimatedObject.h"
#include "AnimatedPlayer.h"
#include "Character.h"
#include "Player.h"
#include "Model.h"

class Map : public Model
{
	public:
		Map(char* json, char* name, Player* player);
		~Map();

		void Update(float dTime);

		char* Model::GetBackground();

		int Model::GetNumberofBlocks();
		Block** Model::GetBlocks();
		int Model::GetNumberofObjects();
		AnimatedObject** Model::GetObjects();
		Character** GetCharacters();

	private:
		char* name;
		char* background;
		int NumberOfBlocks;
		Block** blocks;
		int nObjects;
		Character** characters;
		//Enemy** Enemies;
		//Enemies
		
};