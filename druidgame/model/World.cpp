#include "World.h"
#include <stdio.h>
#include "../util/Geometry.h"
#include <cmath>
#include <box2d/box2d.h>

int32 velocityIterations = 6;
int32 positionIterations = 2;
float timeStep = 1.0f / 60.0f;

World::World()
{
    b2Vec2 gravity(0.0f, 9.81f);
    world = new b2World(gravity);

    activePlayer = new Player(100, 0, world);
    activeMap = new Map("map1", activePlayer, world);
}

World::World(char *savedGame)
{
}

World::~World()
{
    delete activeMap;
    delete world;
}

void World::Update(float dTime)
{
    accumulator += dTime;
    while (accumulator >= timeStep)
    {
        world->Step(timeStep, velocityIterations, positionIterations);
        interactObjects(dTime);
        activeMap->Update(dTime);
        accumulator -= timeStep;
    }
}

//void SaveGame(char* saveName);

Player *World::getPlayer()
{
    return activePlayer;
}

Model *World::getMap()
{
    return activeMap;
}

Character *World::getClosestCharacter(Character *character)
{
    Character *closest = activeMap->GetCharacters()[0];

    //If character is player
    if (character == closest)
        closest = activeMap->GetCharacters()[1];

    //Adjust x to be approx at mouth
    float x = character->getX();
    if (character->getDir() == Character::RIGHT)
        x += character->getWidth();

    for (int i = 0; i < activeMap->GetNumberofObjects(); i++)
    {
        int dist = 0;
        Character *current = activeMap->GetCharacters()[i];
        if (current != character && current->Distance(x, character->getY()) < closest->Distance(x, character->getY()))
        {
            closest = current;
        }
    }

    return closest;
}

void World::interactObjects(float dTime)
{
    Character **characters = activeMap->GetCharacters();

    for (int i = 0; i < activeMap->GetNumberofObjects(); i++)
    {
        if (i != 0)
        { // Don't interact with yourself
            interactPlayerCharacter(activePlayer, characters[i]);
        }
    }
}

void World::interactPlayerCharacter(Character *player, Character *character)
{
    if (player->getMeleeWeapon() != NULL)
    {
        int dir = player->getDir() == Character::LEFT ? -1 : 1;
        float playerX = player->getX() + dir * (player->getWidth() / 2);
        float dist = Geometry::distance(playerX, player->getY(), character->getX(), character->getY());
        character->damage(player->getMeleeWeapon()->getDoneDmg(dist));
    }
}
