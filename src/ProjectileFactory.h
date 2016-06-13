#pragma once
 
class ProjectileFactory
{
public:
	ProjectileFactory();
	void AddProjectileTexture(Render::Texture* tex);
	void SetProjectileDestroyEffect(std::string effName) { _destrEffect = effName; }
	void SetProjectileMoveEffect(std::string effName) { _moveEffect = effName; }
	void SetEffectsDel(EffectsDelegatePtr effDel) { _effDel = effDel; }
	void SetStartPosition(FPoint position) { _cannonPos = position; }
	void SetProjectileSpeed(float speed) { _projSpeed = speed; }
	Projectile AddProjectile(FPoint& destination);

private:
	EffectsDelegatePtr _effDel;
	std::vector<Render::Texture*> _textures;
	std::string _destrEffect;
	std::string _moveEffect;
	FPoint _cannonPos;
	float _projSpeed = 100;
	int _texCount = 0;
	const float _maxTargetSpeed = 100.0f;
	const float _targetRadius = 30.0f;
};

typedef boost::shared_ptr<ProjectileFactory> ProjectileFactoryPtr;
