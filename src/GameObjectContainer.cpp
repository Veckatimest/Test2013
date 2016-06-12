#include "stdafx.h"
#include "GameObject.h"
#include "Target.h"
#include "Projectile.h"
#include "EffectsDelegate.h"
#include "GameObjectContainer.h"

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

void GameObjectContainer::SetEffectsDelegate(EffectsDelegate* effdel)
{
	_effDel = effdel;
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

void GameObjectContainer::RemoveAllObjects()
{
	_projectileList.clear();
	_targetList.clear();
}


void GameObjectContainer::PushGameObject(FPoint position, FPoint speed, float radius)
{
	//GameObject(FPoint startPos, FPoint startSpeed, IRect bounds, float radius);
	_targetList.push_back(Target(position, speed, radius, _effDel));
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
	Target temp(startPos, speed, _targetRadius, _effDel);
	temp.setDestroyEffect(_targetDestrEff);
	temp.setTexture(_targetTex);
	_targetList.push_back(temp);
}

void GameObjectContainer::PushProjectile(FPoint position, FPoint destination)
{
	FPoint speedVect = (destination - position).Normalized() * _projectileSpeed;
	//GameObject(FPoint startPos, FPoint startSpeed, IRect bounds, float radius);
	Projectile temp(position, speedVect, 20, _effDel);
	temp.setTexture(_projectileTex);
	temp.setDestroyEffect(_projectileDestrEff);
	temp.setMoveEffect(_projectileMoveEff);
	_projectileList.push_back(temp);
}

/// Так-то можно было бы наверное устроить тут разбиение сцены на прямоугольники
/// Но так имеет смысл делать если надо детектировать много столковений со многими компонентами.
/// Все эффекты запускаются прямо здесь для экономности.
void GameObjectContainer::Update(float dt, FPoint mousePos)
{
	//Подвигаем все снаряды и проверим стены
	for (std::list<Projectile>::iterator projectile = _projectileList.begin(); projectile != _projectileList.end(); ++projectile)
	{
		projectile->Update(dt, mousePos);
		checkWallCollision(*projectile);
	}
	
	//Подвигаем таргеты и посмотрим нет ли столкновений.
	std::list<Target>::iterator targetIt = _targetList.begin();
	while (targetIt != _targetList.end())
	{
		targetIt->Update(dt, mousePos);
		checkWallCollision(*targetIt);
		std::list<Projectile>::iterator projIt = _projectileList.begin();
		while (projIt != _projectileList.end())
		{
			if (targetIt->isCollided(*projIt))
			{
				targetIt->getHit();
				projIt->getHit();
				//projIt->Finalize();
				break;
			}
			else ++projIt;
		}
		++targetIt;
	}
	_projectileList.remove_if([](GameObject& i){return !i.isAlive(); });
	_targetList.remove_if([](GameObject& i){return !i.isAlive(); });
}

/// И пополняет очередь, и возвращает на нее ссылку.
std::deque<DrawCommand>& GameObjectContainer::GetDrawQueue()
{
	for (std::list<Target>::iterator target = _targetList.begin(); target != _targetList.end(); ++target)
	{
		_drawQueue.push_back(target->Draw());
	}
	for (std::list<Projectile>::iterator projectile = _projectileList.begin(); projectile != _projectileList.end(); ++projectile)
	{
		_drawQueue.push_back(projectile->Draw());
	}
	return _drawQueue;
}

void GameObjectContainer::enableMagnet()
{
	for (std::list<Projectile>::iterator it = _projectileList.begin(); it != _projectileList.end(); ++it){ it->enableMagnet(); }
}

void GameObjectContainer::disableMagnet()
{
	for (std::list<Projectile>::iterator it = _projectileList.begin(); it != _projectileList.end(); ++it){ it->disableMagnet(); }
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

bool GameObjectContainer::checkForDestroy(GameObject& g_object)
{
	return !g_object.isAlive();
}


