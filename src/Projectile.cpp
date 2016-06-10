#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile(FPoint startPos, FPoint startSpeed, float radius) : GameObject(startPos, startSpeed, radius) { }

void Projectile::hitWall(FPoint normal)
{
	alive = false;
}

void Projectile::attachMoveEffect(ParticleEffectPtr effect)
{
	moveEffectPtr = effect;
	effect->SetPos(position);
	effect->Reset();
}