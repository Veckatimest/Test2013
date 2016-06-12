#pragma once

/// �����, ������� ������������� ������ � ��������� ������������ EffectContainer'�, �� �� �� ����
/// ��� ���� �� EffectsContainer ���������� ���� ���������. ������ ��� backward-ducktyping
class EffectsDelegate {
public:
	EffectsDelegate(EffectsContainer& ec);
	ParticleEffectPtr AddEffect(std::string effectName);
	void RemoveEffect(ParticleEffectPtr& effectPtr);
private:
	EffectsContainer& _ec;
};