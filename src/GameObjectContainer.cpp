#include "stdafx.h"
#include "GameObject.h"
#include "Target.h"
#include "Projectile.h"
#include "EffectsDelegate.h"
#include "GameObjectContainer.h"

GameObjectContainer::GameObjectContainer(ProjectileFactoryPtr projFact, TargetFactoryPtr targFact, IRect scenerect) :
_projectileFactory(projFact),
_targetFact(targFact),
_sceneRect(scenerect)
{}

void GameObjectContainer::PushRandTarget() {
	if (!_targetFact) throw "Фабрика не установлена";
	_targetList.push_back(_targetFact->AddRandomTarget(_sceneRect));
}

void GameObjectContainer::PushProjectile(FPoint destination)
{
	if (!_projectileFactory) throw "Фабрика не установлена";
	_projectileList.push_back(_projectileFactory->AddProjectile(destination));
}

/// Так-то можно было бы наверное устроить тут разбиение сцены на прямоугольники
/// Но так имеет смысл делать если надо детектировать много столковений со многими компонентами.
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
			++projIt;
		}
		++targetIt;
	}
	// уберем лишние
	for (std::list<Projectile>::iterator it = _projectileList.begin(); it != _projectileList.end(); )
	{
		if (!it->isAlive()) _projectileList.erase(it++);
		else ++it;
	}

	for (std::list<Target>::iterator it = _targetList.begin(); it != _targetList.end();)
	{
		if (!it->isAlive()) _targetList.erase(it++);
		else ++it;
	}
}

/// Пополняет очередь эффектов, и возвращает на нее ссылку.
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
	IPoint normal = g_object.isInsideRect(_sceneRect);
	if (normal != IPoint(0, 0))
		g_object.hitWall(normal);
}

bool GameObjectContainer::checkForDestroy(GameObject& g_object)
{
	return !g_object.isAlive();
}


