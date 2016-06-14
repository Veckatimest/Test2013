#include "stdafx.h"

#include "GameObject.h"


GameObject::GameObject(FPoint startPos, FPoint startSpeed, float objectRadius, EffectsDelegatePtr p_eff_c)
{
	if (!p_eff_c) " онтейнер эффектов не назначен";
	_position = startPos;
	_speed = startSpeed;
	_radius = objectRadius;
	_alive = true;
	p_effDel = p_eff_c;
}

/// вроде как мы живем в системе у которой координаты начинаютс€ с левого нижнего угла, а не левого верхнего
void GameObject::Update(float dt, FPoint mousePos)
{
	_position += _speed * dt;
}

DrawCommand GameObject::Draw()
{
	return DrawCommand(_texture, _radius * 2, 0, _position);
}

/// в теории-то разные могут быть последстви€
void GameObject::getHit()
{
	_alive = false;
	ParticleEffectPtr projEff = p_effDel->AddEffect(_destroyEffectName);
	projEff->SetPos(_position);
	projEff->Reset();
}

bool GameObject::isCollided(GameObject& other) const
{
	if (_position.GetDistanceTo(other._position) < (_radius + other._radius))
		return true;
	else
		return false;
}

bool GameObject::isAlive() const
{
	return _alive;
}

IPoint GameObject::isInsideRect(IRect& bounds) const
{
	IPoint normal(0, 0);
	if (_position.x - _radius < bounds.x) normal += IPoint(1, 0);
	else if (_position.x + _radius > bounds.width) normal += IPoint(-1, 0);
	if (_position.y - _radius < bounds.y) normal += IPoint(0, 1);
	else if (_position.y + _radius > bounds.height) normal += IPoint(0, -1);
	return normal;
}

void GameObject::setTexture(Render::Texture* texture)
{
	if (texture == NULL) throw "ѕуста€ текстура";
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
