#pragma once
#include "GameObjectContainer.h"


enum GameState {
	inProcess,
	onPause
};

///
/// ������ - �������� ���������� ������� �� ������.
/// �� ������������ ����, � ����� ����� ��������� ������ �������.
///
class TestWidget : public GUI::Widget
{
public:
	TestWidget(const std::string& name, rapidxml::xml_node<>* elem);

	void Draw();
	void Update(float dt);
	
	void AcceptMessage(const Message& message);
	
	bool MouseDown(const IPoint& mouse_pos);
	void MouseMove(const IPoint& mouse_pos);
	void MouseUp(const IPoint& mouse_pos);

private:
	void Init();
	void drawGameObject(const GameObject& go, bool rotate);

private:
	IRect _sceneRect;

	GameState _gameState;
	float _timer; // ������ � ����.
	//
	//float _scale;
	//float _angle;
	//
	Render::Texture* _background;
	//Render::Texture* _tex2;
	//int _curTex;

	EffectsContainer _effCont;
	EffectsDelegate _effDel;
//	ParticleEffectPtr _eff;
};
