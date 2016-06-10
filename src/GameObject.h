#pragma once

class GameObject
{
public:
	GameObject(FPoint startPos);
	GameObject(FPoint startPos, FPoint startSpeed, float objectRadius);
	bool isCollided(GameObject& other);
	bool isPointInside(FPoint point);
	FPoint getPosition();
	float getRadius();
	void Update(float dt);

	// ���������� ��� ������������ �� ������, ��������� ������ ������� � �����������
	virtual void hitWall(FPoint normal) = 0;

	//�������� ����� ���� ������, �� � ����� ������ ��������� ��������� ���� ������� ���� �������
	virtual void getHit();

	bool isAlive();
	void setTexture(std::string texture);
	void setDestroyEffect(std::string effect);
	std::string getTexture();
	std::string getDestroyEffect();

protected:
	/// �� ���� �� �������
	bool alive;
	/// ��������� �������
	FPoint position;
	/// ��������� ��������
	FPoint speed;
	/// ������ �������� ������� (� �� ������ ������� �������)
	float radius;

private:
	/// �����������
	std::string textureName;
	std::string destroyEffectName;
};

