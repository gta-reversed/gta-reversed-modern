#include "StdInc.h"

#include "Scripted2dEffects.h"

void CScripted2dEffects::InjectHooks() {
    RH_ScopedClass(CScripted2dEffects);
    RH_ScopedCategory("Scripts");

    RH_ScopedInstall(Init, 0x6FA6F0, { .reversed = false });
    RH_ScopedInstall(GetEffectPairs, 0x6FA840, { .reversed = false });
    RH_ScopedInstall(GetIndex, 0x6F9F60, { .reversed = false });
    RH_ScopedInstall(AddScripted2DEffect, 0x6FA7C0, { .reversed = false });
    RH_ScopedInstall(ReturnScripted2DEffect, 0x6F9E80, { .reversed = false });
}

// 0x6FA6F0
void CScripted2dEffects::Init() {
    plugin::Call<0x6FA6F0>();
}

// 0x6FA840
CScriptedEffectPairs* CScripted2dEffects::GetEffectPairs(const C2dEffect* effect) {
    return plugin::CallAndReturn<CScriptedEffectPairs*, 0x6FA840, const C2dEffect*>(effect);

    return &ms_effectPairs[GetIndex(effect)];
}

// 0x6F9F60
int32 CScripted2dEffects::GetIndex(const C2dEffect* effect) {
    return plugin::CallAndReturn<int32, 0x6F9F60, const C2dEffect*>(effect);

    for (auto i = 0u; i < ms_effects.size(); i++) {
        if (&ms_effects[i] == effect) {
            return i;
        }
    }
    return -1;
}

// 0x6FA7C0
int32 CScripted2dEffects::AddScripted2DEffect(float radius) {
    return plugin::CallAndReturn<int32, 0x6FA7C0, float>(radius);
}

// 0x6F9E80
void CScripted2dEffects::ReturnScripted2DEffect(int32 index) {
    return plugin::Call<0x6F9E80, int32>(index);

    ms_activated[index] = false;
    return GetPedAttractorManager()->RemoveEffect(&ms_effects[index]);
}

auto CScripted2dEffects::IndexOfEffect(const C2dEffect* effect) -> std::optional<size_t> {
    const auto idx = effect - ms_effects.data();
    if (idx >= 0 && idx <= ms_effects.size()) {
        return (size_t)idx;
    }
    return std::nullopt;
}
