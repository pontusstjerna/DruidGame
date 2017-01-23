#include "Map.h"
#include <stdio.h>

Map::Map(char* json, char* name, AnimatedPlayer* player) : Name(name)
{
	//Blocks = JsonParser.Parse(json);

		if (name == "map1")
		{
			NumberOfBlocks = 10;

			Blocks = new Block*[NumberOfBlocks];
			Blocks[0] = new Block(45, 43, 3, 1, "data/blocks/block_grass1.png");
			Blocks[1] = new Block(4, 50, 200, 10, "data/blocks/block_grass1.png");
			//Blocks[1] = new Block(4, 50, 20000, 10, "data/blocks/block_grass1.png");
			Blocks[2] = new Block(40, 30, 5, 3, "data/blocks/block_stonewall1.png");
			Blocks[3] = new Block(0, 0, 4, 100, "data/blocks/block_stonewall1.png");
			Blocks[4] = new Block(50, 37, 5, 2, "data/blocks/block_grass1.png");
			Blocks[5] = new Block(100, 48, 5, 1, "data/blocks/block_grass1.png");
			Blocks[6] = new Block(106, 47, 5, 1, "data/blocks/block_grass1.png");
			Blocks[7] = new Block(111, 46, 5, 1, "data/blocks/block_grass1.png");
			Blocks[8] = new Block(118, 47, 5, 1, "data/blocks/block_stonewall1.png");
			Blocks[9] = new Block(50, 25, 50, 2, "data/blocks/block_grass1.png");

			Background = "data/maps/map1_bg2.png";


			NumObjects = 2;
			Objects = new AnimatedObject*[NumObjects];
			Objects[0] = player;
			Objects[1] = new Character(50, 25, "data/spritesheets/enemy_human1.png");

		}

		printf("Map %s initialized with %i blocks.\n", Name, NumberOfBlocks);
	}
Map::~Map()
{
	delete[] Blocks;
	delete[] Objects;

	printf("Map %s destroyed.\n", Name);
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
