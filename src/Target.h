#pragma once
#include "GameObject.h"

class Target : public GameObject
{
public:
	Target(FPoint startPos, FPoint startSpeed, float radius);
	virtual void hitWall(FPoint normal) override;
};