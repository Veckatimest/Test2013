#pragma once
#include "GameObjectContainer.h"


enum GameState {
	inProgress,
	onPause
};

///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
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
	void drawCannon(IPoint mousePos);
	TargetFactoryPtr makeTargetFact(EffectsDelegatePtr effDelPtr);
	ProjectileFactoryPtr makeProjFact(EffectsDelegatePtr effDelPtr);

private:
	GameObjectContainer _gameCont;
	EffectsContainer _effCont;

	std::string _gameMessage;
	IRect _sceneRect; // все окно
	IRect _playRect; // зона полета игровых объектов
	IRect _lineRect; // полоса статистики

	FPoint _cannonPos;
	Render::Texture* _cannonTex;

	GameState _gameState;
	float _timer; // Тикает к нулю.
	int _shotCounter;
	Render::Texture* _background;

};
