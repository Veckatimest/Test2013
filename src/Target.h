#pragma once
#include "EffectsDelegate.h"
#include "GameObject.h"

class Target : public GameObject
{
public:
	Target(FPoint startPos, FPoint startSpeed, float objectRadius, EffectsDelegatePtr p_eff_c);
	virtual void hitWall(FPoint normal) override;
};