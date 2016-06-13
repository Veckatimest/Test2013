#pragma once
#include "GameObjectContainer.h"


enum GameState {
	inProgress,
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
	void renderDrawCommand(const DrawCommand& command);
	void restart();
	void drawStatusScreen();
	void drawBottomLine();

private:
	std::string _gameMessage;

	IRect _sceneRect;
	IRect _playRect;
	IRect _lineRect;

	FPoint _cannonPos;

	GameState _gameState;
	float _timer; // ������ � ����.
	int _shotCounter;
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
