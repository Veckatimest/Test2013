#include "stdafx.h"
#include "Target.h"

Target::Target(FPoint startPos, FPoint startSpeed, float radius) : GameObject(startPos, startSpeed, radius) { }

/// ����� ��� ������, ��� ��� ��������� �� ������
/// ���� normal.x = -1, ������ ����������� � ������ �������
/// ���� normal.x = 1, ������ � �����
void Target::hitWall(FPoint normal)
{
	
	if ((normal.x > 0 && speed.x < 0) || // ������ ����� � ���������
			(normal.x < 0 && speed.x > 0))// ������ ������
		speed.x = -speed.x;
	if ((normal.y > 0 && speed.y < 0) || // ...�����
			(normal.y < 0 && speed.y > 0))// ...����
		speed.y = -speed.y;
}