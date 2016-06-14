#pragma once

/// �����, ������� ������������� ������ � ������������ EffectContainer'�, ����� ���
/// �������� ������ � ������� ������.
/// ����� �����, ���� � ���� ��� ������ ���� EffectsContainer, � ��� ���������� ����������� ���� ���������� ��� ���������.
class EffectsDelegate {
public:
	EffectsDelegate(EffectsContainer& ec);
	ParticleEffectPtr AddEffect(std::string effectName);
	void RemoveEffect(ParticleEffectPtr& effectPtr);
private:
	EffectsContainer& _ec;
};

typedef boost::shared_ptr<EffectsDelegate> EffectsDelegatePtr;