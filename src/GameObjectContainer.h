#pragma once

struct EffectTask
{
	std::string id;
	FPoint position;
};

class GameObjectContainer
{
public:
	GameObjectContainer& getInstance();
	
	void PushGameObject(FPoint position, FPoint speed, float radius);
	void PushRandGameObject();
	void PushProjectile(FPoint position, FPoint destination);
	void Update(float dt);
	
	//std::list<GameObject>::iterator GameObjectIterator();
	void setProjectileSpeed(float inputProjectileSpeed);
	void setSceneBounds(IRect rect);
	std::deque<GameObject> getDrawItems();

private:
	GameObjectContainer();
	GameObjectContainer(GameObjectContainer const&) = delete;
	GameObjectContainer& operator= (GameObjectContainer const&) = delete;

	const float maxGameObjectSpeed = 20.0f;
	const float GameObjectRadius = 20.0f;
	IRect sceneRect;
	float projectileSpeed = 30.0f;

	void checkWallCollision(GameObject& g_object);
	void checkForDestroy(GameObject& g_object);
	
	//HitDetector detector;
	//ObjectVisualizer visualizer;
	std::list<GameObject> objectList;
	std::list<GameObject> projectileList;
	EffectsContainer _effCont;
};