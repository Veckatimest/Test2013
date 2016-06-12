#include "stdafx.h"
#include "EffectsDelegate.h"

EffectsDelegate::EffectsDelegate(EffectsContainer& ec) : _ec(ec) {}

ParticleEffectPtr EffectsDelegate::AddEffect(std::string effectName)
{
	ParticleEffectPtr res = _ec.AddEffect(effectName);
	res->Reset();
	return res;
}

void EffectsDelegate::RemoveEffect(ParticleEffectPtr& effectPtr)
{
	effectPtr->Finish();
	effectPtr = NULL;
}
