#include "stdafx.h"
#include "TargetFactory.h"

TargetFactory::TargetFactory():_texCount(0) {}

void TargetFactory::AddTargetTexture(Render::Texture* tex)
{
	if (tex != nullptr)
	{
		_textures.push_back(tex);
		_texCount++;
	}
}

void TargetFactory::AddTargetDestroyEffect(std::string effName)
{
	_destrEffects.push_back(effName);
	_effCount++;
}

Target TargetFactory::AddRandomTarget(IRect& rect)
{
	static int texIndex = 0;
	static int effIndex = 0;

	if (_textures.empty() || _destrEffects.empty()) return Target(FPoint(0, 0), FPoint(0, 0), 1, _effDel);

	float fair_width = rect.Width() - _targetRadius * 2;
	const float lowY = 400.0;
	float fair_height = rect.Height() - _targetRadius * 2 - lowY;
	//position
	float random_var = (float)std::rand() / (float)RAND_MAX;
	FPoint startPos, speed;
	startPos.x = rect.x + fair_width * random_var + _targetRadius;
	random_var = (float)std::rand() / (float)RAND_MAX;
	startPos.y = lowY + rect.y + fair_height * random_var + _targetRadius;
	//speed
	random_var = (float)std::rand() / (float)RAND_MAX;
	speed.x = random_var * _maxTargetSpeed - _maxTargetSpeed / 2;
	random_var = (float)std::rand() / (float)RAND_MAX;
	speed.y = random_var * _maxTargetSpeed - _maxTargetSpeed / 2;
	Target result(startPos, speed, _targetRadius, _effDel);

	result.setDestroyEffect(_destrEffects[effIndex]);
	result.setTexture(_textures[texIndex]);

	++texIndex;
	++effIndex;
	if (texIndex > _texCount - 1) texIndex = 0;
	if (effIndex > _effCount - 1) effIndex = 0;

	return result;
}

