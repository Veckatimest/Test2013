#pragma once
#include "EffectsDelegate.h"
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(FPoint startPos, FPoint startSpeed, float objectRadius, EffectsDelegate* p_eff_c);
	virtual void hitWall(FPoint normal) override;
	virtual void Update(float dt) override;
	virtual void getHit() override;
	std::string getMoveEffect();
	void setMoveEffect(std::string effect);
	void Finalize();
private:
	ParticleEffectPtr _moveEffectPtr;
	std::string _moveEffectName;
};