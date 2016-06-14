#pragma once
#include "DrawCommand.h"
#include "GameObject.h"
#include "Target.h"
#include "Projectile.h"
#include "TargetFactory.h"
#include "ProjectileFactory.h"


struct EffectTask
{
	std::string id;
	FPoint position;
};

class GameObjectContainer
{
public:
	GameObjectContainer() {};
	GameObjectContainer(ProjectileFactoryPtr projFact, TargetFactoryPtr targFact, IRect scenerect);
	void SetTargetFactory(TargetFactoryPtr factory) { _targetFact = factory; }
	void SetProjectileFactory(ProjectileFactoryPtr factory) { _projectileFactory = factory; }
	void SetSceneBounds(IRect rect) { _sceneRect = rect; }

	void PushRandTarget();
	void PushProjectile(FPoint destination);
	void RemoveAllObjects() { _targetList.clear(); _projectileList.clear(); }

	void Update(float dt, FPoint mousePos);
	void enableMagnet();
	void disableMagnet();
	
	std::deque<DrawCommand> & GetDrawQueue();
	const std::list<Target>& GetTargets() { return _targetList; }
	const std::list<Projectile>& GetProjectiles() { return _projectileList; }
private:
	void checkWallCollision(GameObject& g_object);
	bool checkForDestroy(GameObject& g_object);

private:
	IRect _sceneRect;
	std::list<Target> _targetList;
	std::list<Projectile> _projectileList;
	std::deque<DrawCommand> _drawQueue;
	TargetFactoryPtr _targetFact;
	ProjectileFactoryPtr _projectileFactory;
};