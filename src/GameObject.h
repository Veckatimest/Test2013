#pragma once

class GameObject
{
public:
	GameObject(FPoint startPos);
	GameObject(FPoint startPos, FPoint startSpeed, float objectRadius);
	bool isCollided(GameObject& other);
	bool isPointInside(FPoint point);
	FPoint getPosition();
	float getRadius();
	void Update(float dt);

	// Вызывается при столкновении со стеной, принимает вектор нормали к поверхности
	virtual void hitWall(FPoint normal) = 0;

	//Ситуации могут быть разные, но в нашем случае дефолтное поведение гейм обжекта всех устроит
	virtual void getHit();

	bool isAlive();
	void setTexture(std::string texture);
	void setDestroyEffect(std::string effect);
	std::string getTexture();
	std::string getDestroyEffect();

protected:
	/// Не пора ли удалить
	bool alive;
	/// Положение объекта
	FPoint position;
	/// Векторная скорость
	FPoint speed;
	/// Радиус круглого объекта (а мы делаем круглые объекты)
	float radius;

private:
	/// Отображение
	std::string textureName;
	std::string destroyEffectName;
};

