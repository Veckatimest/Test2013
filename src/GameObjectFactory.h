#pragma once

class GameObjectFactory
{
public:
	GameObjectFactory& getInstance();
	void PushGameObject(FPoint position, FPoint speed, float radius);
	void PushRandGameObject();
	std::list<GameObject>::iterator GameObjectIterator();

private:
	GameObjectFactory();
	GameObjectFactory(GameObjectFactory const&) = delete;
	GameObjectFactory& operator= (GameObjectFactory const&) = delete;

	IRect sceneBounds;
	//HitDetector detector;
	//ObjectVisualizer visualizer;
	std::list<GameObject> objectList;
	std::list<GameObject> projectileList;
};