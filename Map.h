#pragma once
#include "Block.h"
#include "AnimatedObject.h"
#include "Character.h"

class Map
{
	public:
		Map(char* json, char* name);
		~Map();

		void Update(float dTime);

		char* GetBackground();

		int GetNumberofBlocks();
		Block** GetBlocks();
		int GetNumberofObjects();
		AnimatedObject** GetObjects();

	private:
		char* Name;
		char* Background;
		int NumberOfBlocks;
		Block** Blocks;
		int NumObjects;
		AnimatedObject** Objects;
		//Enemy** Enemies;
		//Enemies
		
};