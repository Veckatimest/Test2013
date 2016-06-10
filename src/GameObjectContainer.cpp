#include "stdafx.h"
#include "GameObject.h"
#include "Target.h"
#include "Projectile.h"
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
	objectList.push_back(Target(position, speed, radius));
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
	objectList.push_back(Target(startPos, speed, GameObjectRadius));
}

void GameObjectContainer::PushProjectile(FPoint position, FPoint destination)
{
	FPoint speedVect = (destination - position).Normalized() * projectileSpeed;
	//GameObject(FPoint startPos, FPoint startSpeed, IRect bounds, float radius);
	projectileList.push_back(Projectile(position, speedVect, 15));
}

/// “ак-то можно было бы наверное устроить тут разбиение сцены на пр€моугольники
/// Ќо так имеет смысл делать если надо детектировать много столковений со многими компонентами.
void GameObjectContainer::Update(float dt)
{
	//ѕодвигаем все снар€ды и проверим стены
	for (std::list<GameObject>::iterator projectile = projectileList.begin; projectile != projectileList.end(); ++projectile)
	{
		projectile->Update(dt);
		checkWallCollision(*projectile);
	}
		
	//ѕодвигаем таргеты и посмотрим нет ли столкновений.
	for (std::list<GameObject>::iterator targetIt = objectList.begin; targetIt != objectList.end(); ++targetIt)
	{
		targetIt->Update(dt);
		checkWallCollision(*targetIt);
		for (std::list<GameObject>::iterator colliderIt = projectileList.begin; colliderIt != projectileList.end(); ++colliderIt)
		if (targetIt->isCollided(*colliderIt))
		{
			targetIt->getHit();
			if (!targetIt->isAlive())
			{
				ParticleEffectPtr targetEff = _effCont.AddEffect(targetIt->getDestroyEffect());
				targetEff->SetPos(targetIt->getPosition());
				targetEff->Reset();
			}
			ParticleEffectPtr projEff = _effCont.AddEffect(colliderIt->getDestroyEffect());
			projEff->SetPos(colliderIt->getPosition());
			projEff->Reset();
		}
	}
}

void GameObjectContainer::checkWallCollision(GameObject& g_object)
{
	float radius = g_object.getRadius();
	FPoint pos = g_object.getPosition();
	if (pos.x - radius < sceneRect.x) g_object.hitWall(FPoint(1, 0));
	else if (pos.x + radius > sceneRect.width) g_object.hitWall(FPoint(-1, 0));
	if (pos.y - radius < sceneRect.y) g_object.hitWall(FPoint(0, 1));
	else if (pos.y + radius > sceneRect.height) g_object.hitWall(FPoint(0, -1));
}

void checkForDestroy(GameObject& g_object)
{

}


