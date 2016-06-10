#include "stdafx.h"
#include "GameObject.h"
#include "GameObjectContainer.h"

#define RAND_MAX 100

GameObjectContainer::GameObjectContainer() {}

GameObjectContainer& GameObjectContainer::getInstance()
{
	static GameObjectContainer instance;
	return instance;
}

void GameObjectContainer::setSceneBounds(IRect rect)
{
	sceneRect = rect;
}

void GameObjectContainer::setProjectileSpeed(float inputProjectileSpeed)
{
	projectileSpeed = inputProjectileSpeed;
}

void GameObjectContainer::PushGameObject(FPoint position, FPoint speed, float radius)
{
	//GameObject(FPoint startPos, FPoint startSpeed, IRect bounds, float radius);
	objectList.push_back(GameObject(position, speed, sceneRect, radius));
}

void GameObjectContainer::PushRandGameObject()
{
	std::srand(std::time(0));
	//position
	float random_var = (float)std::rand() / (float)RAND_MAX;
	FPoint startPos, speed;
	startPos.x = sceneRect.width * random_var;
	random_var = (float)std::rand() / (float)RAND_MAX;
	startPos.y = sceneRect.height * random_var;
	//speed
	random_var = (float)std::rand() / (float)RAND_MAX;
	speed.x = random_var * maxGameObjectSpeed - maxGameObjectSpeed / 2;
	random_var = (float)std::rand() / (float)RAND_MAX;
	speed.y = random_var * maxGameObjectSpeed - maxGameObjectSpeed / 2;
	objectList.push_back(GameObject(startPos, speed, sceneRect, GameObjectRadius));
}

void GameObjectContainer::PushProjectile(FPoint position, FPoint destination)
{
	FPoint speedVect = (destination - position).Normalized() * projectileSpeed;
	//GameObject(FPoint startPos, FPoint startSpeed, IRect bounds, float radius);
	projectileList.push_back(GameObject(position, speedVect, sceneRect, 15));
}

/// Так-то можно было бы наверное устроить тут разбиение сцены на прямоугольники
/// Но так имеет смысл делать если надо детектировать много столковений со многими компонентами.
void GameObjectContainer::Update(float dt)
{
	for (GameObject item : projectileList)
	{
		item.Update(dt);
	}

	for (GameObject item : objectList)
	{
		item.Update(dt);
		for (GameObject collider : projectileList)
		{
			if (item.isCollided(collider)) item.getHit();
		}
	}
}


