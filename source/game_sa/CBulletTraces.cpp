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
    for (auto& trace : aTraces) {
        if (CTimer::m_snTimeInMilliseconds - trace.m_nCreationTime >= trace.m_nLifeTime) {
            trace.m_bExists = false;
        }
    }
}

void CBulletTraces::AddTrace(const CVector& posMuzzle, const CVector& posBulletHit, eWeaponType weaponType, CEntity* pFromEntity)
{
    if (FindPlayerEntity() != pFromEntity) {
        goto skip_early_outs;
    }
    
    switch (CCamera::GetActiveCamera().m_nMode) {
    case MODE_M16_1STPERSON:
    case MODE_SNIPER:
    case MODE_CAMERA:
    case MODE_ROCKETLAUNCHER:
    case MODE_ROCKETLAUNCHER_HS:
    case MODE_M16_1STPERSON_RUNABOUT:
    case MODE_SNIPER_RUNABOUT:
    case MODE_ROCKETLAUNCHER_RUNABOUT:
    case MODE_ROCKETLAUNCHER_RUNABOUT_HS:
    case MODE_HELICANNON_1STPERSON:
        goto skip_early_outs;
    }

    
    if (FindPlayerEntity()->AsPhysical()->m_vecMoveSpeed.Magnitude() >= 0.05f) {
skip_early_outs:
         CVector dir = posBulletHit - posMuzzle;
         const float traceLengthOriginal = dir.Magnitude();
         dir.Normalise();

         const float traceLengthNew = CGeneral::GetRandomNumberInRange(0.0f, traceLengthOriginal);
         const CVector from = posMuzzle + dir * traceLengthNew;
         const float fRadius = std::min(CGeneral::GetRandomNumberInRange(2.0f, 5.0f), traceLengthOriginal - traceLengthNew);
         AddTrace(
             from,
             from + dir * fRadius,
             0.01f,
             300u,
             70u
         );
    }
}
