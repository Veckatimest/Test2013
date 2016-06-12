#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile(FPoint startPos, FPoint startSpeed, float objectRadius, EffectsDelegate* p_eff_c) : GameObject(startPos, startSpeed, objectRadius, p_eff_c)
{

}

void Projectile::hitWall(FPoint normal)
{
	getHit();
}

void Projectile::getHit()
{
	GameObject::getHit();
	if (_moveEffectPtr){
		_moveEffectPtr->Finish();
		_moveEffectPtr = NULL;
	}
}


void Projectile::Update(float dt)
{
	GameObject::Update(dt);
	if (_moveEffectPtr){
		_moveEffectPtr->SetPos(_position);
	}
}

void Projectile::setMoveEffect(std::string effectName)
{
	_moveEffectName = effectName;
	_moveEffectPtr = p_effDel->AddEffect(_moveEffectName);
	_moveEffectPtr->SetPos(_position);
	_moveEffectPtr->Reset();
}

void Projectile::Finalize()
{

}