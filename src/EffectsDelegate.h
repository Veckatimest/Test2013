#pragma once

/// класс, который предоставл€ет доступ к некоторым возможност€м EffectContainer'а, но не ко всем
/// как если бы EffectsContainer реализовал этот интерфейс. Ќазову это backward-ducktyping
class EffectsDelegate {
public:
	EffectsDelegate(EffectsContainer& ec);
	ParticleEffectPtr AddEffect(std::string effectName);
	void RemoveEffect(ParticleEffectPtr& effectPtr);
private:
	EffectsContainer& _ec;
};