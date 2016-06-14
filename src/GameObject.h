#pragma once
#include "DrawCommand.h"
#include "EffectsDelegate.h"

class GameObject
{
public:
	GameObject(FPoint startPos, FPoint startSpeed, float objectRadius, EffectsDelegatePtr p_eff_c);
	virtual void Update(float dt, FPoint mousePos);
	virtual DrawCommand Draw();
	bool isCollided(GameObject& other) const; // ���������, �� ������������ �� ������� �������
	IPoint isInsideRect(IRect& bounds) const; // ���������, ��������� �� ���� ������ ������ ������, ���� ������� �������, ������ ������� � ��� (��� ������������ �� �������)
	FPoint getPosition() const { return _position; } // ����� �� ������������, ��, � ����� ��� ������ ����.
	FPoint getSpeed() { return _speed; }
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
	Render::Texture* _texture;
	EffectsDelegatePtr p_effDel;

private:
	/// �����������
	std::string _destroyEffectName;
};

