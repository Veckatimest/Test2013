#include "stdafx.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

#define RAND_MAX 100

GameObjectFactory& GameObjectFactory::getInstance()
{
	static GameObjectFactory instance;
	return instance;
}

void GameObjectFactory::PushGameObject(FPoint position, FPoint speed, float radius)
{
	//GameObject(FPoint startPos, FPoint startSpeed, IRect bounds, float radius);
	objectList.push_back(GameObject(position, speed, sceneBounds, radius));
}

void PushRandGameObject()
{
	std::srand(std::time(0));
	int random_variable = std::rand();
}


