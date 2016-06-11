#include "stdafx.h"
#include "TestWidget.h"
#include "GameObjectContainer.h"

const float radToDeg = (180.0f / math::PI);

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, wsize(0, 0, 1024, 768)
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
	Render::Texture* tex2 = Core::resourceManager.Get<Render::Texture>("Circle");
	Render::Texture* smile = Core::resourceManager.Get<Render::Texture>("Smile");
	Render::Texture* rocket = Core::resourceManager.Get<Render::Texture>("Rocket");
	GameObjectContainer& cont = GameObjectContainer::getInstance();
	cont.SetTargetTexture(smile);
	cont.SetTargetDestroyEffect("FindItem2");
	cont.SetProjectileTexture(rocket);
	cont.SetProjectileMoveEffect("Iskra");
	cont.SetProjectileDestroyEffect("FindItem2");
	cont.SetSceneBounds(wsize);

	cont.PushRandGameObject();
	cont.PushRandGameObject();
	cont.PushRandGameObject();
	cont.PushRandGameObject();
	cont.PushRandGameObject();
	cont.PushRandGameObject();
	cont.PushRandGameObject();
	cont.PushRandGameObject();
	cont.PushRandGameObject();

	/*void SetProjectileSpeed(float inputProjectileSpeed);
	void SetTargetTexture(Render::Texture* texture);
	void SetTargetDestroyEffect(std::string effName);
	void SetProjectileTexture(Render::Texture* texture);
	void SetProjectileMoveEffect(std::string effName);
	void SetProjectileDestroyEffect(std::string effName);
	void SetSceneBounds(IRect rect);*/
}

void TestWidget::Draw()
{
	//
	// �������� ������� ��������� ������� ����.
	//
	IPoint mouse_pos = Core::mainInput.GetMousePos();

	GameObjectContainer& cont = GameObjectContainer::getInstance();
	const std::list<Target>& targets = cont.GetTargets();

	for (std::list<Target>::const_iterator tgIt = targets.begin(); tgIt != targets.end(); ++tgIt)
	{
		//
		// ������������ � ���� ������� �������������� ���������, ����� � ����������
		// ����� ���� ������������ ��� �������������� ������� PopMatrix.
		//
		Render::device.PushMatrix();
		//
		// �������� ������� �������������� ���������, ��������� ����� ��������� � ������� ����
		// � ����������� ���������� ������������ ����� ������ ������ ��� z �� ���� _angle.
		//
		FPoint pos = tgIt->getPosition();
		Render::Texture* curtex = tgIt->getTexture();

		Render::device.MatrixTranslate(pos.x, pos.y, 0);
		//Render::device.MatrixRotate(math::Vector3(0, 0, 1), 0);
		IRect texRect = curtex->getBitmapRect();

		//
		// ��� ��������� �������� ����� ������� �������� UV ���������� ��� ����� ��������,
		// ������� ����� �������� �� ������� �������. UV ���������� ������ ���� �������������,
		// �.�., ��� ����������� �� ������� �������� � ��������, ������ ����� ��������
		// ����� 1 (UV ���������� �������� � ��������� 0..1, ���� ����� �� ������ ������ ��
		// ������ �������, ��� ���� � ������ ������������� ��������� �������� REPEAT, ��������
		// ����� ���������� �� ���� ������� ��������������� ���������� ���).
		//

		FRect rect(texRect);
		FRect uv(0, 1, 0, 1);

		float scale = 2 * tgIt->getRadius() / rect.Width();

		curtex->TranslateUV(rect, uv);

		Render::device.MatrixScale(scale);
		Render::device.MatrixTranslate(-texRect.width * 0.5f, -texRect.height * 0.5f, 0.0f);

		//
		// ����������� ��������.
		//
		curtex->Bind();

		//
		// ����� DrawRect() ������� � ����������� ���������� ���������� ������, ��������� �� ����
		// ���������� - �������������, ��������� ��� ���� ������� ���� ��� ������ � ����������� (binded) ��������,
		// ���� ��������� ���������������.
		//
		// ����� ������� DrawRect() ������ ���� ����� Texture::Bind(), ���� SetTexturing(false),
		// ����� ���������� ��������� ����� ���������������.
		//
		Render::DrawRect(rect, uv);
		//curtex->Draw();

		//
		// ��������������� ������� �������������� ���������, ������ �� ����� ��������� �����.
		//
		Render::device.PopMatrix();
	}

	const std::list<Projectile>& bullets = cont.GetProjectiles();
	for (std::list<Projectile>::const_iterator pjIt = bullets.begin(); pjIt != bullets.end(); ++pjIt)
	{
		//
		// ������������ � ���� ������� �������������� ���������, ����� � ����������
		// ����� ���� ������������ ��� �������������� ������� PopMatrix.
		//
		Render::device.PushMatrix();
		//
		// �������� ������� �������������� ���������, ��������� ����� ��������� � ������� ����
		// � ����������� ���������� ������������ ����� ������ ������ ��� z �� ���� _angle.
		//
		FPoint pos = pjIt->getPosition();
		FPoint dir = pjIt->getSpeed().Normalized();
		
		Render::Texture* curtex = pjIt->getTexture();
		float rot = dir.GetAngle();
		Render::device.MatrixTranslate(pos.x, pos.y, 0);
		Render::device.MatrixRotate(math::Vector3(0, 0, 1), radToDeg*rot - 90.0f);
		IRect texRect = curtex->getBitmapRect();

		//
		// ��� ��������� �������� ����� ������� �������� UV ���������� ��� ����� ��������,
		// ������� ����� �������� �� ������� �������. UV ���������� ������ ���� �������������,
		// �.�., ��� ����������� �� ������� �������� � ��������, ������ ����� ��������
		// ����� 1 (UV ���������� �������� � ��������� 0..1, ���� ����� �� ������ ������ ��
		// ������ �������, ��� ���� � ������ ������������� ��������� �������� REPEAT, ��������
		// ����� ���������� �� ���� ������� ��������������� ���������� ���).
		//

		FRect rect(texRect);
		FRect uv(0, 1, 0, 1);

		float scale = 2 * pjIt->getRadius() / rect.Width();

		curtex->TranslateUV(rect, uv);

		Render::device.MatrixScale(scale);
		Render::device.MatrixTranslate(-texRect.width * 0.5f, -texRect.height * 0.5f, 0.0f);

		//
		// ����������� ��������.
		//
		curtex->Bind();

		//
		// ����� DrawRect() ������� � ����������� ���������� ���������� ������, ��������� �� ����
		// ���������� - �������������, ��������� ��� ���� ������� ���� ��� ������ � ����������� (binded) ��������,
		// ���� ��������� ���������������.
		//
		// ����� ������� DrawRect() ������ ���� ����� Texture::Bind(), ���� SetTexturing(false),
		// ����� ���������� ��������� ����� ���������������.
		//
		Render::DrawRect(rect, uv);
		//curtex->Draw();

		//
		// ��������������� ������� �������������� ���������, ������ �� ����� ��������� �����.
		//
		Render::device.PopMatrix();
	}

	//
	// ���� ����� ��������� ��������������� ��� ���������.
	//
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
	//_effCont.Draw();

	Render::BindFont("arial");
	Render::PrintString(924 + 100 / 2, 35, utils::lexical_cast(mouse_pos.x) + ", " + utils::lexical_cast(mouse_pos.y), 1.f, CenterAlign);

}

void TestWidget::Update(float dt)
{
	//
	// ������� ��������� � ���������
	//
	//_effCont.Update(dt);
	GameObjectContainer& cont = GameObjectContainer::getInstance();
	cont.Update(dt);
}

bool TestWidget::MouseDown(const IPoint &mouse_pos)
{
	
	FPoint cannonPos(wsize.width / 2, 30);
	if (Core::mainInput.GetMouseLeftButton())
	{
		GameObjectContainer& cont = GameObjectContainer::getInstance();
		IPoint mouse_pos = Core::mainInput.GetMousePos();
		cont.PushProjectile(cannonPos, FPoint(mouse_pos));
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
