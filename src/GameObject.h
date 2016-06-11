#pragma once

class GameObject
{
public:
	GameObject(FPoint startPos);
	GameObject(FPoint startPos, FPoint startSpeed, float objectRadius);
	virtual void Update(float dt);
	bool isCollided(GameObject& other) const;
	bool isPointInside(FPoint point) const;
	FPoint getPosition() const;
	FPoint getSpeed() const;
	float getRadius() const;
	bool isAlive() const;
	
	virtual void hitWall(FPoint normal) = 0; // ���������� ��� ������������ �� ������, ��������� ������ ������� � �����������
	virtual void getHit(); //�������� ����� ���� ������, �� � ����� ������ ��������� ��������� ���� ������� ���� �������
	
	void setTexture(Render::Texture* texture);
	void setDestroyEffect(std::string effect);
	Render::Texture* getTexture() const;
	std::string getDestroyEffect() const;

protected:
	bool _alive; // �� ���� �� �������
	FPoint _position; // ��������� �������
	FPoint _speed; // ��������� ��������
	float _radius; // ������ �������� ������� (� �� ������ ������� �������)

private:
	/// �����������
	Render::Texture* _texture;
	std::string _destroyEffectName;
};

