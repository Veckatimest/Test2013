#pragma once

class GameObject
{
public:
	GameObject(FPoint startPos);
	GameObject(FPoint startPos, FPoint startSpeed, float objectRadius);
	virtual void Update(float dt);
	bool isCollided(GameObject& other) const;
	bool isPointInside(FPoint point) const;
	FPoint getPosition() const;
	FPoint getSpeed() const;
	float getRadius() const;
	bool isAlive() const;
	
	virtual void hitWall(FPoint normal) = 0; // Вызывается при столкновении со стеной, принимает вектор нормали к поверхности
	virtual void getHit(); //Ситуации могут быть разные, но в нашем случае дефолтное поведение гейм обжекта всех устроит
	
	void setTexture(Render::Texture* texture);
	void setDestroyEffect(std::string effect);
	Render::Texture* getTexture() const;
	std::string getDestroyEffect() const;

protected:
	bool _alive; // Не пора ли удалить
	FPoint _position; // Положение объекта
	FPoint _speed; // Векторная скорость
	float _radius; // Радиус круглого объекта (а мы делаем круглые объекты)

private:
	/// Отображение
	Render::Texture* _texture;
	std::string _destroyEffectName;
};

