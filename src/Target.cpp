#include "stdafx.h"
#include "Target.h"

Target::Target(FPoint startPos, FPoint startSpeed, float objectRadius, EffectsDelegatePtr p_eff_c) : GameObject(startPos, startSpeed, objectRadius, p_eff_c) { }

/// ����� ��� ������, ��� ��� ��������� �� ������
/// ���� normal.x = -1, ������ ����������� � ������ �������
/// ���� normal.x = 1, ������ � �����
void Target::hitWall(FPoint normal)
{
	if ((normal.x > 0 && _speed.x < 0) || // ������ ����� � ���������
			(normal.x < 0 && _speed.x > 0))// ������ ������
		_speed.x = -_speed.x;
	if ((normal.y > 0 && _speed.y < 0) || // ...�����
			(normal.y < 0 && _speed.y > 0))// ...����
		_speed.y = -_speed.y;
}