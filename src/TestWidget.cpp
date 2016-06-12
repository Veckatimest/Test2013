#include "stdafx.h"
#include "SettingsObj.h"
#include "TestWidget.h"

const float radToDeg = (180.0f / math::PI);

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, _sceneRect(0, 0, Render::device.Width(), Render::device.Height())
	, _effCont()
	, _effDel(_effCont)
	, _gameState(GameState::onPause)
	//, _curTex(0)
	//, _timer(0)
	//, _angle(0)
	//, _eff(NULL)
	//, _scale(0.f)
{
	Init();
}

void TestWidget::Init()
{
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
	cont.SetSceneBounds(_sceneRect);
	cont.SetProjectileSpeed(settings.getSpeed());
	_timer = settings.getTime();
	
	for (int i = 0; i < settings.getCount(); i++)
	{
		cont.PushRandGameObject();
	}
}

void TestWidget::drawGameObject(const GameObject& go, bool rotate)
{
	Render::device.PushMatrix();
	FPoint pos = go.getPosition();
	Render::Texture* curtex = go.getTexture();
	Render::device.MatrixTranslate(pos.x, pos.y, 0);
	IRect texRect = curtex->getBitmapRect();
	FRect rect(texRect);
	FRect uv(0, 1, 0, 1);
	float scale = 2 * go.getRadius() / rect.Width();
	curtex->TranslateUV(rect, uv);
	Render::device.MatrixScale(scale);
	if (rotate)
	{
		FPoint dir = go.getSpeed().Normalized();
		float angle = dir.GetAngle() * radToDeg;
		Render::device.MatrixRotate(math::Vector3(0, 0, 1.0f), angle + 90);
	}
		
	Render::device.MatrixTranslate(-texRect.width * 0.5f, -texRect.height * 0.5f, 0.0f);
	curtex->Bind();

	Render::DrawRect(rect, uv);
	//curtex->Draw();
	Render::device.PopMatrix();
}

void TestWidget::Draw()
{
	//
	// �������� ������� ��������� ������� ����.
	//
	IPoint mouse_pos = Core::mainInput.GetMousePos();

	GameObjectContainer& cont = GameObjectContainer::getInstance();
	_background->Draw(IPoint(0, 0));

	if (_gameState == GameState::inProcess)
	{
		const std::list<Target>& targets = cont.GetTargets();
		for (std::list<Target>::const_iterator tgIt = targets.begin(); tgIt != targets.end(); ++tgIt)
		{
			drawGameObject(*tgIt, false);
		}
		const std::list<Projectile>& bullets = cont.GetProjectiles();
		for (std::list<Projectile>::const_iterator pjIt = bullets.begin(); pjIt != bullets.end(); ++pjIt)
		{
			drawGameObject(*pjIt, true);
		}
	}
	else
	{
		Render::device.SetTexturing(false);
		Render::BeginColor(Color(0, 0, 0, 180));
		Render::DrawRect(_sceneRect);
		Render::EndColor();
		Render::BeginColor(Color(51, 204, 255, 255));
		int centerW = 300;
		int centerH = 200;
		Render::DrawRect(IRect(_sceneRect.width/2 - centerW / 2, _sceneRect.height/2 - centerH / 2, centerW, centerH));
		Render::EndColor();
		Render::BindFont("arial");
		Render::BeginColor(Color(0, 153, 51, 255));
		Render::PrintString(_sceneRect.width / 2, _sceneRect.height / 2 + 25, "{font size=22}You can start a game \n by pressing left button {}", 1.f, CenterAlign);
		Render::EndColor();
		Render::device.SetTexturing(true);
	}
	

	Render::device.SetTexturing(false);

	//
	// ����� BeginColor() ������������ � ���� ������� ���� ������ � ������������� �����.
	//
	Render::BeginColor(Color(255, 128, 0, 255));

	//
	// ����� DrawRect() ������� � ����������� ���������� ���������� ������, ��������� �� ����
	// ���������� - �������������, ��������� ��� ���� ������� ���� ��� ������ � ����������� (binded) ��������,
	// ���� ��������� ���������������.
	//
	// ����� ������� DrawRect() ������ ���� ����� Texture::Bind(), ���� SetTexturing(false),
	// ����� ���������� ��������� ����� ���������������.
	//
	Render::DrawRect(924, 0, 100, 100);

	//
	// ����� EndColor() ������� �� ����� ������� ���� ������, �������������� �������.
	//
	Render::EndColor();

	//
	// ����� �������� ���������������.
	//
	Render::device.SetTexturing(true);

	//
	// ������ ��� �������, ������� �������� � ��������� (Update() ��� ���������� �������� �� �����).
	//
	_effCont.Draw();
	//_effCont.Draw();

	Render::BindFont("arial");
	Render::PrintString(924 + 100 / 2, 35, utils::lexical_cast(mouse_pos.x) + ", " + utils::lexical_cast(mouse_pos.y), 1.f, CenterAlign);

}

void TestWidget::Update(float dt)
{

	if (_gameState == GameState::inProcess)
	{
		// ������� ��������� � ���������
		_timer -= dt;
		GameObjectContainer& cont = GameObjectContainer::getInstance();
		_effCont.Update(dt);
		cont.Update(dt);
		if (_timer < 0)
		{
			_gameState = GameState::onPause;
		}
	}
	
}

bool TestWidget::MouseDown(const IPoint &mouse_pos)
{
	FPoint cannonPos(_sceneRect.width / 2, 30);
	if (Core::mainInput.GetMouseLeftButton())
	{
		if (_gameState == GameState::onPause)
		{
			_gameState = GameState::inProcess;
		}
		else {
			GameObjectContainer& cont = GameObjectContainer::getInstance();
			IPoint mouse_pos = Core::mainInput.GetMousePos();
			cont.PushProjectile(cannonPos, FPoint(mouse_pos));
		}
		
	}
	//if (Core::mainInput.GetMouseRightButton())
	//{
	//	//
	//	// ��� ������� �� ������ ������ ����, ������ ������ ������ �� ������.
	//	//
	//	_eff = _effCont.AddEffect("Iskra");
	//	_eff->posX = mouse_pos.x + 0.f;
	//	_eff->posY = mouse_pos.y + 0.f;
	//	_eff->Reset();
	//	
	//	//
	//	// � �������� ���� ������� ��������.
	//	//
	//	_angle += 25;
	//	while (_angle > 360)
	//	{
	//		_angle -= 360;
	//	}
	//}
	//else
	//{
	//	//
	//	// ��� ������� �� ����� ������ ����, ������ ��������� ������, ������� ���������� ���.
	//	//
	//	ParticleEffectPtr eff = _effCont.AddEffect("FindItem2");
	//	eff->posX = mouse_pos.x + 0.f;
	//	eff->posY = mouse_pos.y + 0.f;
	//	eff->Reset();

	//	//
	//	// �������� �������� � 0 �� 1 � ��������.
	//	//
	//	_curTex = 1 - _curTex;
	//}
	return false;
}

void TestWidget::MouseMove(const IPoint &mouse_pos)
{
	//if (_eff)
	//{
	//	//
	//	// ���� ������ ������, �� ���������� ��� � ������� ����.
	//	//
	//	_eff->posX = mouse_pos.x + 0.f;
	//	_eff->posY = mouse_pos.y + 0.f;
	//}
}

void TestWidget::MouseUp(const IPoint &mouse_pos)
{
	//if (_eff)
	//{
	//	//
	//	// ���� ������ ������, �� ��� ���������� ���� ��������� ���.
	//	//
	//	_eff->Finish();
	//	_eff = NULL;
	//}
}

void TestWidget::AcceptMessage(const Message& message)
{
	//
	// ������� ����� ���������� ��������� � �����������.
	//
	// ��������, ��� ����� ������� � ���������� �������� �� �������� ���� ����������
	// ��������� KeyPress � ����� ������� � ���������.
	//
	if (message.getPublisher() == "KeyPress")
	{
		int code = utils::lexical_cast<int>(message.getData());
		if (code < 0)
		{
			//
			// ������������� �������� ���������� ��� ����������� ����� ������,
			// ��������, -VK_RETURN, -VK_ESCAPE � �.�.
			//
			return;
		}

		//
		// ������������� �������� ���������� ��� �������� ��������.
		//
		if (code == 'a')
		{
		}
	}
}
