#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile(FPoint startPos, FPoint startSpeed, float objectRadius, EffectsDelegatePtr p_eff_c) : GameObject(startPos, startSpeed, objectRadius, p_eff_c), _isMagnet(false)
{

}

void Projectile::hitWall(FPoint normal)
{
	if (!(_speed.y > 0 && normal.y > 0))
		getHit();
}

void Projectile::getHit()
{
	GameObject::getHit();
	if (_moveEffectPtr){
		_moveEffectPtr->Finish();
		_moveEffectPtr = NULL;
	}
}


void Projectile::Update(float dt, FPoint mousePos)
{
	// max angle per second
	const float maxAngle = math::PI * 0.5f;
	GameObject::Update(dt, mousePos);
	if (_moveEffectPtr){
		_moveEffectPtr->SetPos(_position);
	}
	if (_isMagnet)
	{
		float realMax = maxAngle * dt;
		//_speed += 200.0f * dt * (mousePos - _position).Normalized();
		float currangle = _speed.GetAngle();
		float needangle = (mousePos - _position).GetAngle();
		float angleDiff = needangle - currangle;
		if (angleDiff > math::PI) angleDiff -= 2 * math::PI;
		if (angleDiff < -math::PI) angleDiff += 2 * math::PI;

		if (math::abs(angleDiff) < realMax)
			_speed.Rotate(angleDiff);
		else if (angleDiff > 0)
			_speed.Rotate(realMax);
		else 
			_speed.Rotate(-realMax);
	}
		
}

DrawCommand Projectile::Draw()
{
	return DrawCommand(_texture, _radius * 2, _speed.GetAngle(), _position);
}

void Projectile::setMoveEffect(std::string effectName)
{
	_moveEffectName = effectName;
	_moveEffectPtr = p_effDel->AddEffect(_moveEffectName);
	_moveEffectPtr->SetPos(_position);
	_moveEffectPtr->Reset();
}
