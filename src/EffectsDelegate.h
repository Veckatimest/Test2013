#pragma once

/// класс, который предоставляет доступ к возможностям EffectContainer'а, таким как
/// добавить эффект и удалить эффект.
/// Нужен затем, чтоб в игре был только один EffectsContainer, и при реализация геймОбжекта была неспособна его испортить.
class EffectsDelegate {
public:
	EffectsDelegate(EffectsContainer& ec);
	ParticleEffectPtr AddEffect(std::string effectName);
	void RemoveEffect(ParticleEffectPtr& effectPtr);
private:
	EffectsContainer& _ec;
};

typedef boost::shared_ptr<EffectsDelegate> EffectsDelegatePtr;