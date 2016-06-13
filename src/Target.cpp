#include "stdafx.h"
#include "Target.h"

Target::Target(FPoint startPos, FPoint startSpeed, float objectRadius, EffectsDelegatePtr p_eff_c) : GameObject(startPos, startSpeed, objectRadius, p_eff_c) { }

/// Стены все прямые, так что усложнять не станем
/// если normal.x = -1, значит столкнулись с правой стенкой
/// если normal.x = 1, значит с левой
void Target::hitWall(FPoint normal)
{
	if ((normal.x > 0 && _speed.x < 0) || // летели влево и врезались
			(normal.x < 0 && _speed.x > 0))// летели вправо
		_speed.x = -_speed.x;
	if ((normal.y > 0 && _speed.y < 0) || // ...вверх
			(normal.y < 0 && _speed.y > 0))// ...вниз
		_speed.y = -_speed.y;
}