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
	// Получаем текущее положение курсора мыши.
	//
	IPoint mouse_pos = Core::mainInput.GetMousePos();

	GameObjectContainer& cont = GameObjectContainer::getInstance();
	const std::list<Target>& targets = cont.GetTargets();

	for (std::list<Target>::const_iterator tgIt = targets.begin(); tgIt != targets.end(); ++tgIt)
	{
		//
		// Проталкиваем в стек текущее преобразование координат, чтобы в дальнейшем
		// можно было восстановить это преобразование вызовом PopMatrix.
		//
		Render::device.PushMatrix();
		//
		// Изменяем текущее преобразование координат, перемещая центр координат в позицию мыши
		// и поворачивая координаты относительно этого центра вокруг оси z на угол _angle.
		//
		FPoint pos = tgIt->getPosition();
		Render::Texture* curtex = tgIt->getTexture();

		Render::device.MatrixTranslate(pos.x, pos.y, 0);
		//Render::device.MatrixRotate(math::Vector3(0, 0, 1), 0);
		IRect texRect = curtex->getBitmapRect();

		//
		// При отрисовке текстуры можно вручную задавать UV координаты той части текстуры,
		// которая будет натянута на вершины спрайта. UV координаты должны быть нормализованы,
		// т.е., вне зависимости от размера текстуры в текселях, размер любой текстуры
		// равен 1 (UV координаты задаются в диапазоне 0..1, хотя ничто не мешает задать их
		// больше единицы, при этом в случае установленной адресации текстуры REPEAT, текстура
		// будет размножена по этой стороне соответствующее количество раз).
		//

		FRect rect(texRect);
		FRect uv(0, 1, 0, 1);

		float scale = 2 * tgIt->getRadius() / rect.Width();

		curtex->TranslateUV(rect, uv);

		Render::device.MatrixScale(scale);
		Render::device.MatrixTranslate(-texRect.width * 0.5f, -texRect.height * 0.5f, 0.0f);

		//
		// Привязываем текстуру.
		//
		curtex->Bind();

		//
		// Метод DrawRect() выводит в графическое устройство квадратный спрайт, состоящий их двух
		// примитивов - треугольников, используя при этом текущий цвет для вершин и привязанную (binded) текстуру,
		// если разрешено текстурирование.
		//
		// Перед вызовом DrawRect() должен быть вызов Texture::Bind(), либо SetTexturing(false),
		// иначе визуальный результат будет непредсказуемым.
		//
		Render::DrawRect(rect, uv);
		//curtex->Draw();

		//
		// Воостанавливаем прежнее преобразование координат, снимая со стека изменённый фрейм.
		//
		Render::device.PopMatrix();
	}

	const std::list<Projectile>& bullets = cont.GetProjectiles();
	for (std::list<Projectile>::const_iterator pjIt = bullets.begin(); pjIt != bullets.end(); ++pjIt)
	{
		//
		// Проталкиваем в стек текущее преобразование координат, чтобы в дальнейшем
		// можно было восстановить это преобразование вызовом PopMatrix.
		//
		Render::device.PushMatrix();
		//
		// Изменяем текущее преобразование координат, перемещая центр координат в позицию мыши
		// и поворачивая координаты относительно этого центра вокруг оси z на угол _angle.
		//
		FPoint pos = pjIt->getPosition();
		FPoint dir = pjIt->getSpeed().Normalized();
		
		Render::Texture* curtex = pjIt->getTexture();
		float rot = dir.GetAngle();
		Render::device.MatrixTranslate(pos.x, pos.y, 0);
		Render::device.MatrixRotate(math::Vector3(0, 0, 1), radToDeg*rot - 90.0f);
		IRect texRect = curtex->getBitmapRect();

		//
		// При отрисовке текстуры можно вручную задавать UV координаты той части текстуры,
		// которая будет натянута на вершины спрайта. UV координаты должны быть нормализованы,
		// т.е., вне зависимости от размера текстуры в текселях, размер любой текстуры
		// равен 1 (UV координаты задаются в диапазоне 0..1, хотя ничто не мешает задать их
		// больше единицы, при этом в случае установленной адресации текстуры REPEAT, текстура
		// будет размножена по этой стороне соответствующее количество раз).
		//

		FRect rect(texRect);
		FRect uv(0, 1, 0, 1);

		float scale = 2 * pjIt->getRadius() / rect.Width();

		curtex->TranslateUV(rect, uv);

		Render::device.MatrixScale(scale);
		Render::device.MatrixTranslate(-texRect.width * 0.5f, -texRect.height * 0.5f, 0.0f);

		//
		// Привязываем текстуру.
		//
		curtex->Bind();

		//
		// Метод DrawRect() выводит в графическое устройство квадратный спрайт, состоящий их двух
		// примитивов - треугольников, используя при этом текущий цвет для вершин и привязанную (binded) текстуру,
		// если разрешено текстурирование.
		//
		// Перед вызовом DrawRect() должен быть вызов Texture::Bind(), либо SetTexturing(false),
		// иначе визуальный результат будет непредсказуемым.
		//
		Render::DrawRect(rect, uv);
		//curtex->Draw();

		//
		// Воостанавливаем прежнее преобразование координат, снимая со стека изменённый фрейм.
		//
		Render::device.PopMatrix();
	}

	//
	// Этот вызов отключает текстурирование при отрисовке.
	//
	Render::device.SetTexturing(false);

	//
	// Метод BeginColor() проталкивает в стек текущий цвет вершин и устанавливает новый.
	//
	Render::BeginColor(Color(255, 128, 0, 255));

	//
	// Метод DrawRect() выводит в графическое устройство квадратный спрайт, состоящий их двух
	// примитивов - треугольников, используя при этом текущий цвет для вершин и привязанную (binded) текстуру,
	// если разрешено текстурирование.
	//
	// Перед вызовом DrawRect() должен быть вызов Texture::Bind(), либо SetTexturing(false),
	// иначе визуальный результат будет непредсказуемым.
	//
	Render::DrawRect(924, 0, 100, 100);

	//
	// Метод EndColor() снимает со стека текущий цвет вершин, восстанавливая прежний.
	//
	Render::EndColor();

	//
	// Опять включаем текстурирование.
	//
	Render::device.SetTexturing(true);

	//
	// Рисуем все эффекты, которые добавили в контейнер (Update() для контейнера вызывать не нужно).
	//
	//_effCont.Draw();

	Render::BindFont("arial");
	Render::PrintString(924 + 100 / 2, 35, utils::lexical_cast(mouse_pos.x) + ", " + utils::lexical_cast(mouse_pos.y), 1.f, CenterAlign);

}

void TestWidget::Update(float dt)
{
	//
	// Обновим контейнер с эффектами
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
	//	// При нажатии на правую кнопку мыши, создаём эффект шлейфа за мышкой.
	//	//
	//	_eff = _effCont.AddEffect("Iskra");
	//	_eff->posX = mouse_pos.x + 0.f;
	//	_eff->posY = mouse_pos.y + 0.f;
	//	_eff->Reset();
	//	
	//	//
	//	// И изменяем угол наклона текстуры.
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
	//	// При нажатии на левую кнопку мыши, создаём временный эффект, который завершится сам.
	//	//
	//	ParticleEffectPtr eff = _effCont.AddEffect("FindItem2");
	//	eff->posX = mouse_pos.x + 0.f;
	//	eff->posY = mouse_pos.y + 0.f;
	//	eff->Reset();

	//	//
	//	// Изменяем значение с 0 на 1 и наоборот.
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
	//	// Если эффект создан, то перемещаем его в позицию мыши.
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
	//	// Если эффект создан, то при отпускании мыши завершаем его.
	//	//
	//	_eff->Finish();
	//	_eff = NULL;
	//}
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
