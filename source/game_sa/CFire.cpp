#include "StdInc.h"

void CFire::Extinguish()
{
    plugin::Call<0x5393F0>();
}

void CFire::ExtinguishWithWater(float fWaterStrength) {
    const float fOriginalStrength = m_fStrength;
    m_fStrength -= fWaterStrength * CTimer::ms_fTimeStep / 50.0f;

    /* Create particles */
    CVector particlePos = m_vecPosition + CVector{
        CGeneral::GetRandomNumberInRange(-1.28f, 1.28f),
        CGeneral::GetRandomNumberInRange(-1.28f, 1.28f),
        CGeneral::GetRandomNumberInRange(-0.64f, 0.64f)
        /* Original code:
        (float)((rand() % 256) - 128) / 100.0f,
        (float)((rand() % 256) - 128) / 100.0f,
        (float)((rand() % 256) - 128) / 200.0f
        */
    };
    FxPrtMult_c prtMult{ 1.0f, 1.0f, 1.0f, 0.6f, 0.75f, 0.0f, 0.4f };
    const auto AddParticle = [&](CVector velocity) {
        g_fx.m_pPrtSmokeII3expand->AddParticle(&particlePos, &velocity, 0.0f, &prtMult, -1.0f, 1.2f, 0.6f, false);
    };
    /* The two particles only differ in velocity */
    AddParticle({ 0.0f, 0.0f, 0.8f });
    AddParticle({ 0.0f, 0.0f, 1.4f });

    /* Re-create fx / extingiush */
    m_nFlags.bBeingExtinguished = true;
    if (m_fStrength >= 0.0f) {
        if ((intmax_t)fOriginalStrength != (intmax_t)m_fStrength) { /* Check if integer part has changed */
            CreateFxSysForStrength(m_vecPosition, nullptr); /* Yes, so needs a new fx */
        }
    } else {
        Extinguish();
    }
}

void CFire::Initialise() {
    return plugin::CallMethod<0x538B30, CFire*>(this);
}

void CFire::Start(CEntity* pCreator, CVector pos, uint32_t nTimeToBurn, uint8_t nGens) {
    m_nFlags = {
      true,  // bActive
      false, // bCreatedByScript
      true,  // bMakesNoise
      false, // bBeingExtinguished
      true   // bFirstGeneration
    };

    m_nTimeToBurn = CTimer::m_snTimeInMilliseconds + (uint32_t)(CGeneral::GetRandomNumberInRange(1.0f, 1.3f) * (float)nTimeToBurn);

    SetTarget(nullptr);
    SetCreator(pCreator);

    m_nNumGenerationsAllowed = nGens;
    m_fStrength = 1.0f;
    m_vecPosition = pos;

    CreateFxSysForStrength(m_vecPosition, nullptr);
}
}

void CFire::CreateFxSysForStrength(const CVector& point, RwMatrixTag* m) {
    return plugin::CallMethod<0x539360, CFire*, const CVector&, RwMatrixTag*>(this, point, m);
}

void CFire::Extinguish() {
    return plugin::CallMethod<0x5393F0, CFire*>(this);
}

void CFire::ProcessFire() {
    return plugin::CallMethod<0x53A570, CFire*>(this);
}

void CFire::DestroyFx() {
    if (m_pFxSystem) {
        g_fxMan.DestroyFxSystem(m_pFxSystem);   
        m_pFxSystem = nullptr;
    }
}

void CFire::SetTarget(CEntity* pTarget) {
    if (m_pEntityTarget)
        m_pEntityTarget->CleanUpOldReference(&m_pEntityTarget); /* Assume old target's m_pFire is not pointing to `*this` */
    m_pEntityTarget = pTarget; /* assign, even if its null, to clear it */
    if (pTarget) {
        m_pEntityTarget->RegisterReference(&m_pEntityTarget);
        switch (pTarget->m_nType) { /* Set target to point to `*this` */
        case eEntityType::ENTITY_TYPE_PED:
            static_cast<CPed*>(pTarget)->m_pFire = this;
            break;
        case eEntityType::ENTITY_TYPE_VEHICLE:
            static_cast<CVehicle*>(pTarget)->m_pFire = this;
            break;
        }
    }
}

void CFire::SetCreator(CEntity* pCreator) {
    if (m_pEntityCreator)
        m_pEntityCreator->CleanUpOldReference(&m_pEntityCreator);
    m_pEntityCreator = pCreator; /* assign, even if its null, to clear it */
    if (pCreator)
        pCreator->RegisterReference(&m_pEntityCreator);
}

