#pragma once

class GameObject
{
public:
	GameObject(FPoint startPos);
	GameObject(FPoint startPos, FPoint startSpeed, IRect bounds, float radius);
	void setSpeed(FPoint new_speed);
	bool isCollided(GameObject& other);
	bool isPointInside(FPoint point);

	FPoint getPosition();
	void updatePosition(float dt);

	void kill();

	~GameObject();

private:
	bool alive;
	/// ��������� �������
	FPoint position;
	/// ��������� ��������
	FPoint speed;
	/// ������� �����, ��� �� ��������� (??)
	IRect boundingRect;
	/// ������ �������� ������� (� �� ������ ������� �������)
	float radius;

};

