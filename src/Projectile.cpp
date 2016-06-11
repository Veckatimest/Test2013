#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile(FPoint startPos, FPoint startSpeed, float radius) : GameObject(startPos, startSpeed, radius) { }

void Projectile::hitWall(FPoint normal)
{
	_alive = false;
}

void Projectile::Update(float dt)
{
	GameObject::Update(dt);
	if (_moveEffectPtr){
		_moveEffectPtr->SetPos(_position);
	}
}

void Projectile::AttachMoveEffect(ParticleEffectPtr effect)
{
	_moveEffectPtr = effect;
	effect->SetPos(_position);
	effect->Reset();
}

void Projectile::Finalize()
{
	if (_moveEffectPtr){
		_moveEffectPtr->Finish();
		_moveEffectPtr = NULL;
	}
}