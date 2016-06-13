#include "Target.h"

class TargetFactory
{
public:
	TargetFactory();
	void AddTargetTexture(Render::Texture* tex);
	void AddTargetDestroyEffect(std::string effName);
	void SetEffectsDel(EffectsDelegatePtr effDel) { _effDel = effDel; }
	Target AddRandomTarget(IRect& rect);

private:
	EffectsDelegatePtr _effDel;
	std::vector<Render::Texture*> _textures;
	std::vector<std::string> _destrEffects;
	int _texCount = 0;
	int _effCount = 0;
	const float _maxTargetSpeed = 100.0f;
	const float _targetRadius = 50.0f;
};

//typedef boost::shared_ptr<TargetFactory> TargetFactoryPtr;
typedef boost::shared_ptr<TargetFactory> TargetFactoryPtr;