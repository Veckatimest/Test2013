#pragma once

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
	const float maxGameObjectSpeed = 20.0f;
	const float GameObjectRadius = 10.0f;

	GameObjectContainer();
	GameObjectContainer(GameObjectContainer const&) = delete;
	GameObjectContainer& operator= (GameObjectContainer const&) = delete;
	float projectileSpeed = 30.0f;
	IRect sceneRect;
	//HitDetector detector;
	//ObjectVisualizer visualizer;
	std::list<GameObject> objectList;
	std::list<GameObject> projectileList;
	std::deque<GameObject> drawObjects;
};