#pragma once
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
	void Update(float dt);
	
	void SetProjectileSpeed(float inputProjectileSpeed);
	void SetTargetTexture(Render::Texture* texture);
	void SetTargetDestroyEffect(std::string effName);
	void SetProjectileTexture(Render::Texture* texture);
	void SetProjectileMoveEffect(std::string effName);
	void SetProjectileDestroyEffect(std::string effName);
	void SetSceneBounds(IRect rect);

	const std::list<Target>& GetTargets();
	const std::list<Projectile>& GetProjectiles();
private:
	GameObjectContainer();
	GameObjectContainer(GameObjectContainer const&) = delete;
	GameObjectContainer& operator= (GameObjectContainer const&) = delete;
	void checkWallCollision(GameObject& g_object);

private:
	const float _maxGameObjectSpeed = 100.0f;
	const float _targetRadius = 30.0f;
	IRect _sceneRect;
	float _projectileSpeed = 60.0f;
	// возможно это следует вынести в фабрики прожектайлов и таргетов...
	Render::Texture* _targetTex;
	std::string _targetDestrEff;
	Render::Texture* _projectileTex;
	std::string _projectileDestrEff;
	std::string _projectileMoveEff;

	// ¬от бы иметь умные указатели и создать коллекцию типа GameObject
	std::list<Target> _targetList;
	std::list<Projectile> _projectileList;
	EffectsContainer _effCont;
};