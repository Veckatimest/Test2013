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

//inline void intrusive_ptr_add_ref(EffectsDelegate* x){
//	++x->references;
//}
//
//inline void intrusive_ptr_release(EffectsDelegate* x){
//	if (--x->references == 0)
//		delete x;
//}

typedef boost::shared_ptr<EffectsDelegate> EffectsDelegatePtr;