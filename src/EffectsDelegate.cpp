#include "stdafx.h"
#include "EffectsDelegate.h"

EffectsDelegate::EffectsDelegate(EffectsContainer& ec) : _ec(ec) {}

ParticleEffectPtr EffectsDelegate::AddEffect(std::string effectName)
{
	try {
		ParticleEffectPtr res = _ec.AddEffect(effectName);
		res->Reset();
		return res;
	}
	catch (...)
	{
		throw "Похоже, что эффект не загружен";
		return nullptr;
	}
	
	
}

void EffectsDelegate::RemoveEffect(ParticleEffectPtr& effectPtr)
{
	effectPtr->Finish();
	effectPtr = NULL;
}
