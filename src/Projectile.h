#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(FPoint startPos, FPoint startSpeed, float objectRadius);
	virtual void hitWall(FPoint normal) override;
	virtual void Update(float dt) override;
	std::string getMoveEffect();
	void AttachMoveEffect(ParticleEffectPtr effect);
	void Finalize();
private:
	ParticleEffectPtr _moveEffectPtr;
};