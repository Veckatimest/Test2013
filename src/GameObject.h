#pragma once
#include "DrawCommand.h"
#include "EffectsDelegate.h"

class GameObject
{
public:
	GameObject(FPoint startPos, FPoint startSpeed, float objectRadius, EffectsDelegatePtr p_eff_c);
	virtual void Update(float dt, FPoint mousePos);
	virtual DrawCommand Draw();
	bool isCollided(GameObject& other) const; // проверяет, не пересекаются ли игровые объекты
	IPoint isInsideRect(IRect& bounds) const; // проверяет, находится ли весь объект внутри границ, если пересек границу, вернет нормаль к ней (для столкновения со стенами)
	FPoint getPosition() const { return _position; } // нигде не используются, но, я думаю они должны быть.
	FPoint getSpeed() { return _speed; }
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
	Render::Texture* _texture;
	EffectsDelegatePtr p_effDel;

private:
	/// Отображение
	std::string _destroyEffectName;
};

