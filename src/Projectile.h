#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(FPoint startPos, FPoint startSpeed, float objectRadius);
	virtual void hitWall(FPoint normal) override;
	std::string getMoveEffect();
	void attachMoveEffect(ParticleEffectPtr effect);
private:
	ParticleEffectPtr moveEffectPtr;
};