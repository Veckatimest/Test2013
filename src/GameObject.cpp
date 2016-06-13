#include "stdafx.h"

#include "GameObject.h"


GameObject::GameObject(FPoint startPos)
{
	_position = startPos;
	_alive = true;
}

GameObject::GameObject(FPoint startPos, FPoint startSpeed, float objectRadius, EffectsDelegatePtr p_eff_c)
{
	_position = startPos;
	_speed = startSpeed;
	_radius = objectRadius;
	_alive = true;
	p_effDel = p_eff_c;
}

/// вроде как мы живем в системе у которой координаты начинаются с левого нижнего угла, а не левого верхнего
void GameObject::Update(float dt, FPoint mousePos)
{
	_position += _speed * dt;
}

DrawCommand GameObject::Draw()
{
	return DrawCommand(_texture, _radius * 2, 0, _position);
}

/// в теории-то разные могут быть последствия
void GameObject::getHit()
{
	_alive = false;
	ParticleEffectPtr projEff = p_effDel->AddEffect(_destroyEffectName);
	projEff->SetPos(_position);
	projEff->Reset();
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
