#pragma once
#include "Block.h"

class Map
{
	public:
		Map(char* json, char* name);
		~Map();

		char* GetBackground();

		int GetNumberofBlocks();
		Block** GetBlocks();

	private:
		char* Name;
		char* Background;
		int NumberOfBlocks;
		Block* Blocks[];
};