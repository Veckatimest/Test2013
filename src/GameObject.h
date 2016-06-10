#pragma once

class GameObject
{
public:
	GameObject(FPoint startPos);
	GameObject(FPoint startPos, FPoint startSpeed, IRect bounds, float radius);
	void setSpeed(FPoint new_speed);
	bool isCollided(GameObject& other);
	bool isPointInside(FPoint point);

	FPoint getPosition();
	void updatePosition(float dt);

	void kill();

	~GameObject();

private:
	bool alive;
	/// Положение объекта
	FPoint position;
	/// Векторная скорость
	FPoint speed;
	/// Размеры сцены, где он находится (??)
	IRect boundingRect;
	/// Радиус круглого объекта (а мы делаем круглые объекты)
	float radius;

};

