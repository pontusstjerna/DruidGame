#pragma once
#include "Block.h"
#include "Enemy.h"

class Map
{
	public:
		Map(char* json, char* name);
		~Map();

		char* GetBackground();

		int GetNumberofBlocks();
		Block** GetBlocks();
		AnimatedObject** GetObjects();

	private:
		char* Name;
		char* Background;
		int NumberOfBlocks;
		Block** Blocks;
		Enemy** Enemies;
		
};