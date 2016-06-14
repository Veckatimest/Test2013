#include "stdafx.h"
#include "Projectile.h"
#include "ProjectileFactory.h"

ProjectileFactory::ProjectileFactory(){}

void ProjectileFactory::AddProjectileTexture(Render::Texture* tex)
{
	if (tex != nullptr)
	{
		_textures.push_back(tex);
		_texCount++;
	}
}

Projectile ProjectileFactory::AddProjectile(FPoint& destination)
{
	static int texIndex = 0;
	if (_texCount == 0) throw "Нет текстур";
	FPoint speedVect = (destination - _cannonPos).Normalized() * _projSpeed;
	Projectile temp(_cannonPos, speedVect, 25, _effDel);
	temp.setTexture(_textures[texIndex]);
	temp.setDestroyEffect(_destrEffect);
	temp.setMoveEffect(_moveEffect);

	texIndex++;

	if (texIndex > _texCount - 1)
		texIndex = 0;

	return temp;
}