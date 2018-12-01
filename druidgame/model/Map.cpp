#include "Map.h"
#include <stdio.h>

Map::Map(char* name, Player* player) : name(name), player(player)
{
	//Blocks = JsonParser.Parse(json);

		if (name == "map1")
		{
			NumberOfBlocks = 11;

			blocks = new Block*[NumberOfBlocks];
			blocks[0] = new Block(45, 43, 3, 1, "block_grass1");
			blocks[1] = new Block(4, 50, 200, 10, "block_grass1");
			//Blocks[1] = new Block(4, 50, 20000, 10, "data/blocks/block_grass1.png");
			blocks[2] = new Block(40, 30, 5, 3, "block_stonewall1");
			blocks[3] = new Block(0, 0, 4, 100, "block_stonewall1");
			blocks[4] = new Block(50, 37, 5, 2, "block_grass1");
			blocks[5] = new Block(100, 48, 5, 1, "block_grass1");
			blocks[6] = new Block(106, 47, 5, 1, "block_grass1");
			blocks[7] = new Block(111, 46, 5, 1, "block_grass1");
			blocks[8] = new Block(118, 47, 5, 1, "block_stonewall1");
			blocks[9] = new Block(50, 25, 50, 2, "block_grass1");
			blocks[10] = new Block(204, 0, 2, 100, "block_stonewall1");

			background = "map1_bg2";


			nObjects = 1;
			characters = new Character*[nObjects];
			characters[0] = player;
			//characters[1] = new Enemy(125, 25, "enemy_human1", 1);

			/*for (int i = 2; i < nObjects; i++)
			{
				characters[i] = new Enemy(150 + i * 20, 25, "enemy_human1", i);
			}*/

		}

		printf("Map %s initialized with %i blocks.\n", name, NumberOfBlocks);
	}
Map::~Map()
{
	for (int i = 1; i < nObjects; i++)
	{
		delete characters[i];
	}

	for (int i = 1; i < NumberOfBlocks; i++)
	{
		delete blocks[i];
	}

	delete[] blocks;
	delete[] characters;

	

	printf("Map %s destroyed.\n", name);
}

void Map::Update(float dTime)
{
	for (int i = 0; i < nObjects; i++)
	{
		if(characters[i]->getState() != GameObject::DEAD)
			characters[i]->update(dTime);
	}
}

char* Map::GetBackground()
{
	return background;
}

int Map::GetNumberofBlocks()
{
	return NumberOfBlocks;
}

Block** Map::GetBlocks()
{
	return blocks;
}

int Map::GetNumberofObjects()
{
	return nObjects;
}

GameObject** Map::GetObjects()
{
	return (GameObject**)characters;
}

Character** Map::GetCharacters()
{
	return characters;
}

AnimatedPlayer* Map::getPlayer() {
    return player;
}
