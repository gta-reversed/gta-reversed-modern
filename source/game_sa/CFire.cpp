#include "StdInc.h"

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

    m_nTimeToBurn = CTimer::GetTimeInMS() + (uint32_t)(CGeneral::GetRandomNumberInRange(1.0f, 1.3f) * (float)nTimeToBurn);

    SetTarget(nullptr);
    SetCreator(pCreator);

    m_nNumGenerationsAllowed = nGens;
    m_fStrength = 1.0f;
    m_vecPosition = pos;

    CreateFxSysForStrength(m_vecPosition, nullptr);
}

void CFire::Start(CEntity* pCreator, CEntity* pTarget, uint32_t nTimeToBurn, uint8_t nGens) {
    switch (pTarget->m_nType) {
    case eEntityType::ENTITY_TYPE_PED: {
        auto pPedTarget = static_cast<CPed*>(pTarget);
        pPedTarget->m_pFire = this;
        CCrime::ReportCrime(
            pPedTarget->m_nPedType == ePedType::PED_TYPE_COP ? eCrimeType::CRIME_SET_COP_PED_ON_FIRE : eCrimeType::CRIME_SET_PED_ON_FIRE,
            pPedTarget,
            static_cast<CPed*>(pCreator)
        );
        break;
    }
    case eEntityType::ENTITY_TYPE_VEHICLE: {
        auto pVehTarget = static_cast<CVehicle*>(pTarget);
        pVehTarget->m_pFire = this;
        CCrime::ReportCrime(
            eCrimeType::CRIME_SET_CAR_ON_FIRE,
            reinterpret_cast<CPed*>(pVehTarget), // TODO: Change ReportCrime's signature to take CEntity* here..
            static_cast<CPed*>(pCreator)
        );
        break;
    }
    case eEntityType::ENTITY_TYPE_OBJECT: {
        static_cast<CObject*>(pTarget)->m_pFire = this;
        break;
    }
    }

    m_nFlags = {
        true,  // bActive
        false, // bCreatedByScript
        true,  // bMakesNoise
        false, // bBeingExtinguished
        true   // bFirstGeneration
    };

    m_nNumGenerationsAllowed = nGens;
    m_fStrength = 1.0f;
    m_vecPosition = pTarget->GetPosition();

    if (pTarget->IsPed() && static_cast<CPed*>(pTarget)->IsPlayer())
        m_nTimeToBurn = CTimer::GetTimeInMS() + 2333;
    else if (pTarget->IsVehicle())
        m_nTimeToBurn = CTimer::GetTimeInMS() + CGeneral::GetRandomNumberInRange(0, 1000) + 3000;
    else
        m_nTimeToBurn = CTimer::GetTimeInMS() + CGeneral::GetRandomNumberInRange(0, 1000) + nTimeToBurn;

    SetTarget(pTarget);
    SetCreator(pCreator);

    CreateFxSysForStrength(m_vecPosition, nullptr);
}

void CFire::Start(CVector pos, float fStrength, CEntity* pTarget, uint8_t nGens) {
    SetTarget(pTarget);
    SetCreator(nullptr);

    m_nFlags = {
        true,  // bActive
        true,  // bCreatedByScript
        true,  // bMakesNoise
        false, // bBeingExtinguished
        true   // bFirstGeneration
    };

    m_nNumGenerationsAllowed = nGens;
    m_fStrength = fStrength;
    m_vecPosition = pos;

    if (pTarget) {
        switch (pTarget->m_nType) { /* Set target's `m_pFire` to `this` */
        case eEntityType::ENTITY_TYPE_PED:
            static_cast<CPed*>(pTarget)->m_pFire = this;
            break;
        case eEntityType::ENTITY_TYPE_VEHICLE:
            static_cast<CVehicle*>(pTarget)->m_pFire = this;
            break;
        }
    }

    CreateFxSysForStrength(pTarget ? pos : pTarget->GetPosition(), nullptr);
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
    if (pTarget)
        m_pEntityTarget->RegisterReference(&m_pEntityTarget); /* Assume caller set pTarget->m_pFire */
}

void CFire::SetCreator(CEntity* pCreator) {
    if (m_pEntityCreator)
        m_pEntityCreator->CleanUpOldReference(&m_pEntityCreator);
    m_pEntityCreator = pCreator; /* assign, even if its null, to clear it */
    if (pCreator)
        pCreator->RegisterReference(&m_pEntityCreator);
}

