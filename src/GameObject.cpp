#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(FPoint startPos)
{
	_position = startPos;
	_alive = true;
}

GameObject::GameObject(FPoint startPos, FPoint startSpeed, float objectRadius)
{
	_position = startPos;
	_speed = startSpeed;
	_radius = objectRadius;
	_alive = true;
}

/// вроде как мы живем в системе у которой координаты начинаются с левого нижнего угла, а не левого верхнего
void GameObject::Update(float dt)
{
	_position += _speed * dt;
}

/// в теории-то разные могут быть последствия
void GameObject::getHit()
{
	_alive = false;
}

FPoint GameObject::getPosition() const
{
	return _position;
}

FPoint GameObject::getSpeed() const
{
	return _speed;
}

bool GameObject::isCollided(GameObject& other) const
{
	if (_position.GetDistanceTo(other._position) < (_radius + other._radius))
		return true;
	else
		return false;
}

bool GameObject::isPointInside(FPoint point) const
{
	if (_position.GetDistanceTo(point) < _radius)
		return true;
	else
		return false;
}

bool GameObject::isAlive() const
{
	return _alive;
}

float GameObject::getRadius() const
{
	return _radius;
}

void GameObject::setTexture(Render::Texture* texture)
{
	_texture = texture;
}

Render::Texture* GameObject::getTexture() const
{
	return _texture;
}

void GameObject::setDestroyEffect(std::string effect)
{
	_destroyEffectName = effect;
}

std::string GameObject::getDestroyEffect() const
{
	return _destroyEffectName;
}