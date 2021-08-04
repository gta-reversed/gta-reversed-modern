#include "StdInc.h"

CBulletTrace(&CBulletTraces::aTraces)[16] = *(CBulletTrace(*)[16])0xC7C748;

void CBulletTraces::InjectHooks()
{
    ReversibleHooks::Install("CBulletTraces", "Init", 0x721D50, &CBulletTraces::Init);
    ReversibleHooks::Install("CBulletTraces", "AddTrace", 0x723750, static_cast<void(*)(const CVector&, const CVector&, float, uint32_t, uint8_t)>(&CBulletTraces::AddTrace));
    ReversibleHooks::Install("CBulletTraces", "Render", 0x723C10, &CBulletTraces::Render);
    ReversibleHooks::Install("CBulletTraces", "Update", 0x723FB0, &CBulletTraces::Update);
    ReversibleHooks::Install("CBulletTraces", "AddTrace", 0x726AF0, static_cast<void(*)(const CVector&, const CVector&, eWeaponType, CEntity*)>(&CBulletTraces::AddTrace));
}

void CBulletTraces::Init()
{
    for (auto& trace : aTraces) {
        trace.m_bExists = false;
    }
}

void CBulletTraces::AddTrace(const CVector& from, const CVector& to, float radius, uint32_t dissapearTime, uint8_t alpha)
{
    return plugin::Call<0x723750, const CVector&, const CVector&, float, uint32_t, uint8_t>(from, to, radius, dissapearTime, alpha);
}

void CBulletTraces::Render()
{
    return plugin::Call<0x723C10>();
}

void CBulletTraces::Update()
{
    return plugin::Call<0x723FB0>();
}

void CBulletTraces::AddTrace(const CVector& from, const CVector& to, eWeaponType weaponType, CEntity* pFromEntity)
{
    return plugin::Call<0x726AF0, const CVector&, const CVector&, int32_t, CEntity*>(from, to, weaponType, pFromEntity);
}
