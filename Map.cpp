#include "Map.h"

Map::Map(char* json, char* name) : Name(name)
{
	//Blocks = JsonParser.Parse(json);

		if (name == "map1")
		{
			NumberOfBlocks = 2;

			Blocks = new Block*[NumberOfBlocks];
			Blocks[0] = new Block(5, 5, 3, 2, "data/blocks/block1.png");
			Blocks[1] = new Block(5, 20, 3, 2, "data/blocks/block1.png");

			Background = "data/maps/map1_bg.png";

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
