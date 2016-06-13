#pragma once
#include "DrawCommand.h"
#include "EffectsDelegate.h"

class GameObject
{
public:
	GameObject(FPoint startPos);
	GameObject(FPoint startPos, FPoint startSpeed, float objectRadius, EffectsDelegatePtr p_eff_c);
	virtual void Update(float dt, FPoint mousePos);
	virtual DrawCommand Draw();
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
	Render::Texture* _texture;
	EffectsDelegatePtr p_effDel;

private:
	/// �����������
	std::string _destroyEffectName;
};

