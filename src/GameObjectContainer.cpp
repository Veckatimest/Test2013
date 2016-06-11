#include "stdafx.h"
#include "GameObject.h"
#include "Target.h"
#include "Projectile.h"
#include "GameObjectContainer.h"

//#define RAND_MAX 100

GameObjectContainer::GameObjectContainer() {}

GameObjectContainer& GameObjectContainer::getInstance()
{
	static GameObjectContainer _instance;
	return _instance;
}

const std::list<Target>& GameObjectContainer::GetTargets()
{
	return _targetList;
}

const std::list<Projectile>& GameObjectContainer::GetProjectiles()
{
	return _projectileList;
}

void GameObjectContainer::SetSceneBounds(IRect rect)
{
	_sceneRect = rect;
}

void GameObjectContainer::SetProjectileSpeed(float inputProjectileSpeed)
{
	_projectileSpeed = inputProjectileSpeed;
}

void GameObjectContainer::SetTargetTexture(Render::Texture* texture)
{
	_targetTex = texture;
}

void GameObjectContainer::SetTargetDestroyEffect(std::string effName)
{
	_targetDestrEff = effName;
}

void GameObjectContainer::SetProjectileTexture(Render::Texture* texture)
{
	_projectileTex = texture;
}

void GameObjectContainer::SetProjectileMoveEffect(std::string effName)
{
	_projectileMoveEff = effName;
}

void GameObjectContainer::SetProjectileDestroyEffect(std::string effName)
{
	_projectileDestrEff = effName;
}


void GameObjectContainer::PushGameObject(FPoint position, FPoint speed, float radius)
{
	//GameObject(FPoint startPos, FPoint startSpeed, IRect bounds, float radius);
	_targetList.push_back(Target(position, speed, radius));
}

void GameObjectContainer::PushRandGameObject()
{
	float fair_width = _sceneRect.Width() - _targetRadius * 2;
	float fair_height = _sceneRect.Height() - _targetRadius * 2;
	//position
	float random_var = (float)std::rand() / (float)RAND_MAX;
	FPoint startPos, speed;
	startPos.x = fair_width * random_var + _targetRadius;
	random_var = (float)std::rand() / (float)RAND_MAX;
	startPos.y = fair_height * random_var + _targetRadius;
	//speed
	random_var = (float)std::rand() / (float)RAND_MAX;
	speed.x = random_var * _maxGameObjectSpeed - _maxGameObjectSpeed / 2;
	random_var = (float)std::rand() / (float)RAND_MAX;
	speed.y = random_var * _maxGameObjectSpeed - _maxGameObjectSpeed / 2;
	Target temp(startPos, speed, _targetRadius);
	temp.setDestroyEffect(_targetDestrEff);
	temp.setTexture(_targetTex);
	_targetList.push_back(temp);
}

void GameObjectContainer::PushProjectile(FPoint position, FPoint destination)
{
	FPoint speedVect = (destination - position).Normalized() * _projectileSpeed;
	//GameObject(FPoint startPos, FPoint startSpeed, IRect bounds, float radius);
	Projectile temp(position, speedVect, 30);
	temp.setTexture(_projectileTex);
	temp.setDestroyEffect(_projectileDestrEff);
	//temp.AttachMoveEffect()
	_projectileList.push_back(temp);
}

/// “ак-то можно было бы наверное устроить тут разбиение сцены на пр€моугольники
/// Ќо так имеет смысл делать если надо детектировать много столковений со многими компонентами.
void GameObjectContainer::Update(float dt)
{
	_effCont.Update(dt);
	//ѕодвигаем все снар€ды и проверим стены
	for (std::list<Projectile>::iterator projectile = _projectileList.begin(); projectile != _projectileList.end(); ++projectile)
	{
		projectile->Update(dt);
		checkWallCollision(*projectile);
	}
	
	//ѕодвигаем таргеты и посмотрим нет ли столкновений.
	std::list<Target>::iterator targetIt = _targetList.begin();
	while (targetIt != _targetList.end())
	{
		targetIt->Update(dt);
		checkWallCollision(*targetIt);
		std::list<Projectile>::iterator colliderIt = _projectileList.begin();
		//while (colliderIt != _projectileList.end())
		//{
		//	if (targetIt->isCollided(*colliderIt))
		//	{
		//		targetIt->getHit();
		//		if (!targetIt->isAlive())
		//		{
		//			ParticleEffectPtr targetEff = _effCont.AddEffect(targetIt->getDestroyEffect());
		//			targetEff->SetPos(targetIt->getPosition());
		//			targetEff->Reset();
		//			_targetList.erase(targetIt++);
		//		}
		//		else ++targetIt;
		//		ParticleEffectPtr projEff = _effCont.AddEffect(colliderIt->getDestroyEffect());
		//		projEff->SetPos(colliderIt->getPosition());
		//		projEff->Reset();
		//		colliderIt->Finalize();
		//		_projectileList.erase(colliderIt++);
		//	}
		//	else ++colliderIt;
		//}
		++targetIt;
	}


	//for (std::list<Target>::iterator targetIt = _targetList.begin(); targetIt != _targetList.end(); ++targetIt)
	//{
	//	targetIt->Update(dt);
	//	checkWallCollision(*targetIt);
	//	for (std::list<Projectile>::iterator colliderIt = _projectileList.begin(); colliderIt != _projectileList.end(); ++colliderIt)
	//		if (targetIt->isCollided(*colliderIt))
	//		{
	//			targetIt->getHit();
	//			if (!targetIt->isAlive())
	//			{
	//				ParticleEffectPtr targetEff = _effCont.AddEffect(targetIt->getDestroyEffect());
	//				targetEff->SetPos(targetIt->getPosition());
	//				targetEff->Reset();
	//			}
	//			ParticleEffectPtr projEff = _effCont.AddEffect(colliderIt->getDestroyEffect());
	//			projEff->SetPos(colliderIt->getPosition());
	//			projEff->Reset();
	//			colliderIt->Finalize();
	//		}
	//}
}

void GameObjectContainer::checkWallCollision(GameObject& g_object)
{
	float radius = g_object.getRadius();
	FPoint pos = g_object.getPosition();
	if (pos.x - radius < _sceneRect.x) g_object.hitWall(FPoint(1, 0));
	else if (pos.x + radius > _sceneRect.width) g_object.hitWall(FPoint(-1, 0));
	if (pos.y - radius < _sceneRect.y) g_object.hitWall(FPoint(0, 1));
	else if (pos.y + radius > _sceneRect.height) g_object.hitWall(FPoint(0, -1));
}

void checkForDestroy(GameObject& g_object)
{

}


