#include "Map.h"

Map::Map(char* json, char* name, AnimatedObject* player) : Name(name)
{
	//Blocks = JsonParser.Parse(json);

		if (name == "map1")
		{
			NumberOfBlocks = 5;

			Blocks = new Block*[NumberOfBlocks];
			Blocks[0] = new Block(45, 43, 3, 1, "data/blocks/block_grass1.png");
			Blocks[1] = new Block(0, 50, 20, 10, "data/blocks/block_grass1.png");
			Blocks[2] = new Block(40, 30, 5, 3, "data/blocks/block_stonewall1.png");
			Blocks[3] = new Block(10, 0, 4, 100, "data/blocks/block_stonewall1.png");
			Blocks[4] = new Block(62, 35, 5, 2, "data/blocks/block_grass1.png");

			Background = "data/maps/map1_bg2.png";


			NumObjects = 1;
			Objects = new AnimatedObject*[NumObjects];
			Objects[0] = player;

		}


	}
Map::~Map()
{
	delete[] Blocks;
	delete[] Objects;
}

void Map::Update(float dTime)
{
	for (int i = 0; i < NumObjects; i++)
	{
		Objects[i]->Update(dTime);
	}
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

int Map::GetNumberofObjects()
{
	return NumObjects;
}

AnimatedObject** Map::GetObjects()
{
	return Objects;
}
