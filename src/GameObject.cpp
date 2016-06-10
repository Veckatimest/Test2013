#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(FPoint startPos)
{
	position = startPos;
	alive = true;
}

GameObject::GameObject(FPoint startPos, FPoint startSpeed, float objectRadius)
{
	position = startPos;
	speed = startSpeed;
	radius = objectRadius;
	alive = true;
}

/// ����� ��� �� ����� � ������� � ������� ���������� ���������� � ������ ������� ����, � �� ������ ��������
void GameObject::Update(float dt)
{
	position += speed * dt;
}

FPoint GameObject::getPosition()
{
	return position;
}

bool GameObject::isCollided(GameObject& other)
{
	if (position.GetDistanceTo(other.position) < (radius + other.radius))
		return true;
	else
		return false;
}

bool GameObject::isPointInside(FPoint point)
{
	if (position.GetDistanceTo(point) < radius)
		return true;
	else
		return false;
}

/// � ������-�� ������ ����� ���� �����������
void GameObject::getHit()
{
	alive = false;
}

inline bool GameObject::isAlive()
{
	return alive;
}

inline float GameObject::getRadius()
{
	return radius;
}

void GameObject::setTexture(std::string texture)
{
	textureName = texture;
}

std::string GameObject::getTexture()
{
	return textureName;
}

void GameObject::setDestroyEffect(std::string effect)
{
	destroyEffectName = effect;
}

std::string GameObject::getDestroyEffect()
{
	return destroyEffectName;
}