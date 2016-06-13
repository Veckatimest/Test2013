#include "stdafx.h"
#include "SettingsObj.h"
#include "TestWidget.h"

const float radToDeg = (180.0f / math::PI);

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, _sceneRect(0, 0, Render::device.Width(), Render::device.Height())
	, _playRect(0, 35, Render::device.Width(), Render::device.Height())
	, _lineRect(0, 0, Render::device.Width(), 35)
	, _effCont()
	, _effDel(_effCont)
	, _gameState(GameState::onPause)
	, _cannonPos(_sceneRect.width / 2, 45)
	//, _curTex(0)
	, _timer(0)
	, _shotCounter(0)
	//, _angle(0)
	//, _eff(NULL)
	//, _scale(0.f)
{
	Init();
}

void TestWidget::restart()
{
	GameObjectContainer& cont = GameObjectContainer::getInstance();
	SettingsObj& settings = SettingsObj::getInstance();
	_timer = settings.getTime();
	_shotCounter = 0;
	for (int i = 0; i < settings.getCount(); i++)
	{
		cont.PushRandGameObject();
	}
}

void TestWidget::Init()
{
	_gameMessage = "{font size=18}You can start a game by pressing \n left button. Use mouse right button \n  to correct missle direction{}";
	Render::Texture* tex1 = Core::resourceManager.Get<Render::Texture>("btnStart_Text");
	Render::Texture* fighter = Core::resourceManager.Get<Render::Texture>("Fighter");
	Render::Texture* rocket = Core::resourceManager.Get<Render::Texture>("Rocket");
	_background = Core::resourceManager.Get<Render::Texture>("Background");
	GameObjectContainer& cont = GameObjectContainer::getInstance();
	SettingsObj& settings = SettingsObj::getInstance();
	cont.SetEffectsDelegate(&_effDel);
	cont.SetTargetTexture(fighter);
	cont.SetTargetDestroyEffect("Explode");
	cont.SetProjectileTexture(rocket);
	cont.SetProjectileMoveEffect("Engine");
	cont.SetProjectileDestroyEffect("Explode");
	cont.SetSceneBounds(_playRect);
	cont.SetProjectileSpeed(settings.getSpeed());
}

void TestWidget::drawStatusScreen()
{
	Render::device.SetTexturing(false);
	Render::BeginColor(Color(0, 0, 0, 180));
	Render::DrawRect(_sceneRect);
	Render::EndColor();
	Render::BeginColor(Color(51, 204, 255, 255));
	int centerW = 400;
	int centerH = 300;
	Render::DrawRect(IRect(_sceneRect.width / 2 - centerW / 2, _sceneRect.height / 2 - centerH / 2, centerW, centerH));
	Render::EndColor();
	Render::BindFont("arial");
	Render::BeginColor(Color(0, 153, 51, 255));
	Render::PrintString(_sceneRect.width / 2, _sceneRect.height / 2 + 25, _gameMessage, 1.f, CenterAlign);
	Render::EndColor();
	Render::device.SetTexturing(true);
}

void TestWidget::drawBottomLine()
{
	Render::device.SetTexturing(false);
	Render::BeginColor(Color(40, 160, 230, 255));
	Render::DrawRect(_lineRect);
	Render::EndColor();
	Render::BindFont("arial");
	Render::BeginColor(Color(153, 204, 255, 255));
	Render::PrintString(20, 25, std::string("{font size=18}You've got ") + utils::lexical_cast((int)_timer) + std::string(" s {}"), 1.f, LeftAlign);//_shotCounter
	Render::PrintString(400, 25, std::string("{font size=18}You've fired ") + utils::lexical_cast(_shotCounter) + std::string(" missles {}"), 1.f, LeftAlign);
	Render::EndColor();
	Render::device.SetTexturing(true);
}

void TestWidget::renderDrawCommand(const DrawCommand& command)
{
	Render::device.PushMatrix();
	FPoint pos = command.position;
	Render::Texture* curtex = command.tex;
	Render::device.MatrixTranslate(pos.x, pos.y, 0);
	IRect texRect = curtex->getBitmapRect();
	FRect rect(texRect);
	//FRect uv(0, 1, 0, 1);
	float scale = command.size / rect.Width();
	//curtex->TranslateUV(rect, uv);
	Render::device.MatrixScale(scale);
	if (command.angle != 0.0f)
		Render::device.MatrixRotate(math::Vector3(0, 0, 1.0f), command.angle*radToDeg);

	Render::device.MatrixTranslate(-texRect.width * 0.5f, -texRect.height * 0.5f, 0.0f);
	//curtex->Bind();

	//Render::DrawRect(rect, uv);
	curtex->Draw();
	Render::device.PopMatrix();
}

void TestWidget::Draw()
{
	GameObjectContainer& cont = GameObjectContainer::getInstance();
	_background->Draw(IPoint(0, 0));
	drawBottomLine();

	if (_gameState == GameState::inProgress)
	{
		std::deque<DrawCommand>& draws = cont.GetDrawQueue();
		while (!draws.empty())
		{
			renderDrawCommand(draws.front());
			draws.pop_front();
		}
	}
	else
		drawStatusScreen();
	
	_effCont.Draw();
	//_effCont.Draw();

	//Render::BindFont("arial");
	//Render::PrintString(924 + 100 / 2, 35, utils::lexical_cast(mouse_pos.x) + ", " + utils::lexical_cast(mouse_pos.y), 1.f, CenterAlign);

}

void TestWidget::Update(float dt)
{
	IPoint mouse_pos = Core::mainInput.GetMousePos();
	if (_gameState == GameState::inProgress)
	{
		// Обновим контейнер с эффектами
		_timer -= dt;
		GameObjectContainer& cont = GameObjectContainer::getInstance();
		_effCont.Update(dt);
		cont.Update(dt, mouse_pos);
		if ((_timer < 0) || cont.GetTargets().empty())
		{
			cont.RemoveAllObjects();
			_effCont.KillAllEffects();
			_gameState = GameState::onPause;
			if (_timer < 0)
				_gameMessage = "{font size=18}You've lost! Restart a game by \n pressing left button. Use mouse right button \n to correct missle direction{}";
			else
			{
				SettingsObj& settings = SettingsObj::getInstance();
				int accuracy = math::round(100.0f * (float)settings.getCount() / (float)_shotCounter);
				_gameMessage = "{font size=18}You won! Restart a game by pressing \n left button. Use mouse right button \n to correct missle direction{} \n\n Shot " \
					+ utils::lexical_cast(_shotCounter) + " missles. \n Your accuracy is " + utils::lexical_cast(accuracy);
			}
				
		}
	}
}

bool TestWidget::MouseDown(const IPoint &mouse_pos)
{
	GameObjectContainer& cont = GameObjectContainer::getInstance();
	if (Core::mainInput.GetMouseLeftButton())
	{
		if (_gameState == GameState::onPause)
		{
			restart();
			_gameState = GameState::inProgress;
		}
		else {
			IPoint mouse_pos = Core::mainInput.GetMousePos();
			cont.PushProjectile(_cannonPos, FPoint(mouse_pos));
			_shotCounter++;
		}
	}
	
	if (Core::mainInput.GetMouseRightButton())
	{
		cont.enableMagnet();
	}

	return false;
}

void TestWidget::MouseMove(const IPoint &mouse_pos)
{
	//if (_eff)
	//{
	//	//
	//	// Если эффект создан, то перемещаем его в позицию мыши.
	//	//
	//	_eff->posX = mouse_pos.x + 0.f;
	//	_eff->posY = mouse_pos.y + 0.f;
	//}
}

void TestWidget::MouseUp(const IPoint &mouse_pos)
{
	GameObjectContainer& cont = GameObjectContainer::getInstance();
	cont.disableMagnet();
}

void TestWidget::AcceptMessage(const Message& message)
{
	//
	// Виджету могут посылаться сообщения с параметрами.
	//
	// Например, при вводе символа с клавиатуры виджетам на активном слое посылается
	// сообщение KeyPress с кодом символа в параметре.
	//
	if (message.getPublisher() == "KeyPress")
	{
		int code = utils::lexical_cast<int>(message.getData());
		if (code < 0)
		{
			//
			// Отрицательные значения посылаются для виртуальных кодов клавиш,
			// например, -VK_RETURN, -VK_ESCAPE и т.д.
			//
			return;
		}

		//
		// Положительные значения посылаются для символов алфавита.
		//
		if (code == 'a')
		{
		}
	}
}
