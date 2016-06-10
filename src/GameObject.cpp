#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(FPoint startPos)
{
	position = startPos;
	alive = true;
}

GameObject::GameObject(FPoint startPos, FPoint startSpeed, IRect bounds, float objectRadius)
{
	position = startPos;
	speed = startSpeed;
	boundingRect = bounds;
	radius = objectRadius;
	alive = true;
}
/// вроде как мы живем в системе у которой координаты начинаются с левого нижнего угла, а не левого верхнего
void GameObject::updatePosition(float dt)
{
	position += speed * dt;
	if (position.x - radius < boundingRect.x) {
		speed.x = -speed.x;
		position.x = radius;
	} else if (position.x + radius > boundingRect.x + boundingRect.width) {
		speed.x = -speed.x;
		position.x = boundingRect.x + boundingRect.width - radius;
	}
	if (position.y - radius < boundingRect.y) {
		position.y = radius;
		speed.y = -speed.y;
	} else if (position.y + radius < boundingRect.y + boundingRect.height) {
		position.y = boundingRect.y + boundingRect.height - radius;
		speed.y = -speed.y;
	}
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

void GameObject::setSpeed(FPoint new_speed)
{
	speed = new_speed;
}

void GameObject::kill()
{
	alive = false;
}

