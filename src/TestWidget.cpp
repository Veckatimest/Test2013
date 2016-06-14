#include "stdafx.h"
#include "SettingsObj.h"
#include "TestWidget.h"

const float radToDeg = (180.0f / math::PI);

TargetFactoryPtr TestWidget::makeTargetFact(EffectsDelegatePtr effDelPtr)
{
	Render::Texture* fighter1 = Core::resourceManager.Get<Render::Texture>("Fighter1");
	Render::Texture* fighter2 = Core::resourceManager.Get<Render::Texture>("Fighter2");
	Render::Texture* fighter3 = Core::resourceManager.Get<Render::Texture>("Fighter3");
	Render::Texture* fighter4 = Core::resourceManager.Get<Render::Texture>("Fighter4");
	Render::Texture* fighter5 = Core::resourceManager.Get<Render::Texture>("Fighter5");
	Render::Texture* fighter6 = Core::resourceManager.Get<Render::Texture>("Fighter6");
	TargetFactoryPtr targetFactoryPtr(new TargetFactory());
	targetFactoryPtr->SetEffectsDel(effDelPtr);
	targetFactoryPtr->AddTargetDestroyEffect("Explode");
	targetFactoryPtr->AddTargetTexture(fighter1);
	targetFactoryPtr->AddTargetTexture(fighter2);
	targetFactoryPtr->AddTargetTexture(fighter3);
	return targetFactoryPtr;
}

ProjectileFactoryPtr TestWidget::makeProjFact(EffectsDelegatePtr effDelPtr)
{
	SettingsObj& settings = SettingsObj::getInstance();
	Render::Texture* rocket = Core::resourceManager.Get<Render::Texture>("Rocket");
	ProjectileFactoryPtr projFactPtr(new ProjectileFactory() );
	projFactPtr->SetEffectsDel(effDelPtr);
	projFactPtr->AddProjectileTexture(rocket);
	projFactPtr->SetStartPosition(_cannonPos);
	projFactPtr->SetProjectileMoveEffect("Engine");
	projFactPtr->SetProjectileDestroyEffect("Explode");
	projFactPtr->SetProjectileSpeed(settings.getSpeed());
	return projFactPtr;
}

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, _effCont()
	, _sceneRect(0, 0, Render::device.Width(), Render::device.Height())
	, _cannonPos(_sceneRect.width / 2, 45)
	, _lineRect(0, Render::device.Height() - 35, Render::device.Width(), 35)
	, _playRect(0, 0, Render::device.Width(), Render::device.Height() - 35)
	, _gameCont()
	, _gameState(GameState::onPause)
	, _timer(0)
	, _shotCounter(0)
{
	Init();
}

void TestWidget::restart()
{
	SettingsObj& settings = SettingsObj::getInstance();
	_timer = settings.getTime();
	_shotCounter = 0;
	for (int i = 0; i < settings.getCount(); i++)
	{
		_gameCont.PushRandTarget();
	}
}

void TestWidget::Init()
{
	EffectsDelegatePtr effDelPtr(new EffectsDelegate(_effCont));
	TargetFactoryPtr targFact = makeTargetFact(effDelPtr);
	ProjectileFactoryPtr projFact = makeProjFact(effDelPtr);
	_gameCont.SetSceneBounds(_playRect);
	_gameCont.SetTargetFactory(targFact);
	_gameCont.SetProjectileFactory(projFact);
	_gameMessage = "{font size=24}You can start a game by pressing \n left button. Use mouse right button \n  to correct missle direction{}";
	_background = Core::resourceManager.Get<Render::Texture>("Background");
	_cannonTex = Core::resourceManager.Get<Render::Texture>("FighterMe");
	SettingsObj& settings = SettingsObj::getInstance();
}

void TestWidget::drawStatusScreen()
{
	Render::device.SetTexturing(false);
	Render::BeginColor(Color(0, 0, 0, 180));
	Render::DrawRect(_sceneRect);
	Render::EndColor();
	/*Render::BeginColor(Color(51, 204, 255, 255));
	int centerW = 400;
	int centerH = 300;
	Render::DrawRect(IRect(_sceneRect.width / 2 - centerW / 2, _sceneRect.height / 2 - centerH / 2, centerW, centerH));
	Render::EndColor();*/
	Render::BindFont("arial");
	Render::BeginColor(Color(255, 179, 26, 255));
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
	
	Render::PrintString(_lineRect.x + 20, _lineRect.y + 25, std::string("{font size=18}You've got ") + utils::lexical_cast((int)_timer) + std::string(" s {}"), 1.f, LeftAlign);//_shotCounter
	Render::PrintString(_lineRect.x + 400, _lineRect.y + 25, std::string("{font size=18}You've fired ") + utils::lexical_cast(_shotCounter) + std::string(" missles {}"), 1.f, LeftAlign);
	Render::EndColor();
	Render::device.SetTexturing(true);
}

void TestWidget::drawCannon(IPoint mousePos)
{
	float angle = (FPoint(mousePos) - _cannonPos).GetAngle();
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_cannonPos.x, _cannonPos.y, 0);
	IRect texRect = _cannonTex->getBitmapRect();
	Render::device.MatrixScale(0.7f);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1.0f), angle*radToDeg);
	Render::device.MatrixTranslate(-texRect.width * 0.2f, -texRect.height * 0.5f, 0.0f);
	
	_cannonTex->Draw();
	Render::device.PopMatrix();
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
	float scale = command.size / rect.Height();
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
	IPoint mouse_pos = Core::mainInput.GetMousePos();
	_background->Draw(IPoint(0, 0));

	if (_gameState == GameState::inProgress)
	{
		std::deque<DrawCommand>& draws = _gameCont.GetDrawQueue();
		while (!draws.empty())
		{
			renderDrawCommand(draws.front());
			draws.pop_front();
		}
		drawCannon(mouse_pos);
		drawBottomLine();
	}
	else
		drawStatusScreen();
	_effCont.Draw();
}

void TestWidget::Update(float dt)
{
	IPoint mouse_pos = Core::mainInput.GetMousePos();
	if (_gameState == GameState::inProgress)
	{
		// Обновим контейнер с эффектами
		_timer -= dt;
		_effCont.Update(dt);
		_gameCont.Update(dt, mouse_pos);
		if ((_timer < 0) || _gameCont.GetTargets().empty())
		{
			_gameCont.RemoveAllObjects();
			_effCont.KillAllEffects();
			_gameState = GameState::onPause;
			if (_timer < 0)
				_gameMessage = "{font size=18}You've lost! Restart a game by \n pressing left button. Use mouse right button \n to correct missles direction{}";
			else
			{
				SettingsObj& settings = SettingsObj::getInstance();
				int accuracy = math::round(100.0f * (float)settings.getCount() / (float)_shotCounter);
				_gameMessage = "{font size=18}You won! Restart a game by pressing \n left button. Use mouse right button \n to correct missles direction{} \n\n Shot " \
					+ utils::lexical_cast(_shotCounter) + " missles. \n Your accuracy is " + utils::lexical_cast(accuracy);
			}
				
		}
	}
}

bool TestWidget::MouseDown(const IPoint &mouse_pos)
{
	if (Core::mainInput.GetMouseLeftButton())
	{
		if (_gameState == GameState::onPause)
		{
			restart();
			_gameState = GameState::inProgress;
		}
		else {
			IPoint mouse_pos = Core::mainInput.GetMousePos();
			_gameCont.PushProjectile(FPoint(mouse_pos));
			_shotCounter++;
		}
	}

	if (Core::mainInput.GetMouseRightButton())
	{
		_gameCont.enableMagnet();
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
	_gameCont.disableMagnet();
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
