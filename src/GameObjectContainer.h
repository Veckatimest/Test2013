#pragma once
#include "DrawCommand.h"
#include "GameObject.h"
#include "Target.h"
#include "Projectile.h"


struct EffectTask
{
	std::string id;
	FPoint position;
};

class GameObjectContainer
{
public:
	static GameObjectContainer& getInstance();
	
	void PushGameObject(FPoint position, FPoint speed, float radius);
	void PushRandGameObject();
	void PushProjectile(FPoint position, FPoint destination);
	void Update(float dt, FPoint mousePos);
	void enableMagnet();
	void disableMagnet();
	
	void SetProjectileSpeed(float inputProjectileSpeed);
	void SetTargetCount(int count);
	void SetPlayTime(int time);
	void SetTargetTexture(Render::Texture* texture);
	void SetTargetDestroyEffect(std::string effName);
	void SetProjectileTexture(Render::Texture* texture);
	void SetProjectileMoveEffect(std::string effName);
	void SetProjectileDestroyEffect(std::string effName);
	void SetSceneBounds(IRect rect);
	void SetEffectsDelegate(EffectsDelegate* effdel);
	void RemoveAllObjects();
	std::deque<DrawCommand> & GetDrawQueue();

	const std::list<Target>& GetTargets();
	const std::list<Projectile>& GetProjectiles();
private:
	GameObjectContainer();
	GameObjectContainer(GameObjectContainer const&) = delete;
	GameObjectContainer& operator= (GameObjectContainer const&) = delete;
	void checkWallCollision(GameObject& g_object);
	bool checkForDestroy(GameObject& g_object);

private:
	const float _maxGameObjectSpeed = 100.0f;
	const float _targetRadius = 30.0f;
	IRect _sceneRect;
	float _projectileSpeed = 300.0f;
	// возможно это следует вынести в фабрики прожектайлов и таргетов...
	Render::Texture* _targetTex;
	std::string _targetDestrEff;
	Render::Texture* _projectileTex;
	std::string _projectileDestrEff;
	std::string _projectileMoveEff;

	std::list<Target> _targetList;
	std::list<Projectile> _projectileList;
	std::deque<DrawCommand> _drawQueue;

	EffectsDelegate* _effDel;
};