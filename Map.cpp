#include "Map.h"

Map::Map(char* json, char* name) : Name(name)
{
	//Blocks = JsonParser.Parse(json);

		if (name == "map1")
		{
			NumberOfBlocks = 3;

			Blocks = new Block*[NumberOfBlocks];
			Blocks[0] = new Block(45, 45, 2, 1, "data/blocks/block1.png");
			Blocks[1] = new Block(0, 50, 20, 10, "data/blocks/block_grass1.png");
			Blocks[2] = new Block(20, 42, 5, 1, "data/blocks/block_grass1.png");

			Background = "data/maps/map1_bg2.png";

		}
	}
Map::~Map()
{
	for (int i = 0; i < NumberOfBlocks; i++)
	{
		delete Blocks[i];
	}
	delete Blocks;
}

char* Map::GetBackground()
{
	return Background;
}

int Map::GetNumberofBlocks()
{
	return NumberOfBlocks;
}

Block** Map::GetBlocks()
{
	return Blocks;
}
