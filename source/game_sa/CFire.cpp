#include "StdInc.h"

#include "CFire.h"

void CFire::Initialise() {
    return plugin::CallMethod<0x538B30, CFire*>(this);
}

void CFire::ExtinguishWithWater(float fWaterStrength) {
    const float fOriginalStrength = m_fStrength;
    m_fStrength -= fWaterStrength * CTimer::GetTimeStepInSeconds();

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

    /* Re-create fx / extinguish */
    beingExtinguished = true;
    if (m_fStrength >= 0.0f) {
        if ((intmax_t)fOriginalStrength != (intmax_t)m_fStrength) { /* Check if integer part has changed */
            CreateFxSysForStrength(m_vecPosition, nullptr); /* Yes, so needs a new fx */
        }
    } else {
        Extinguish();
    }
}

void CFire::Start(CEntity* creator, CVector pos, uint32_t nTimeToBurn, uint8_t nGens) {
    active = true;
    createdByScript = false;
    makesNoise = true;
    beingExtinguished = false;
    firstGeneration = true;

    m_nTimeToBurn = CTimer::GetTimeInMS() + (uint32_t)(CGeneral::GetRandomNumberInRange(1.0f, 1.3f) * (float)nTimeToBurn);

    SetTarget(nullptr);
    SetCreator(creator);

    m_nNumGenerationsAllowed = nGens;
    m_fStrength = 1.0f;
    m_vecPosition = pos;

    CreateFxSysForStrength(m_vecPosition, nullptr);
}

void CFire::Start(CEntity* creator, CEntity* target, uint32_t nTimeToBurn, uint8_t nGens) {
    switch (target->m_nType) {
    case eEntityType::ENTITY_TYPE_PED: {
        auto pPedTarget = static_cast<CPed*>(target);
        pPedTarget->m_pFire = this;
        CCrime::ReportCrime(
            pPedTarget->m_nPedType == ePedType::PED_TYPE_COP ? eCrimeType::CRIME_SET_COP_PED_ON_FIRE : eCrimeType::CRIME_SET_PED_ON_FIRE,
            pPedTarget,
            static_cast<CPed*>(creator)
        );
        break;
    }
    case eEntityType::ENTITY_TYPE_VEHICLE: {
        auto pVehTarget = static_cast<CVehicle*>(target);
        pVehTarget->m_pFire = this;
        CCrime::ReportCrime(
            eCrimeType::CRIME_SET_CAR_ON_FIRE,
            reinterpret_cast<CPed*>(pVehTarget), // TODO: Change ReportCrime's signature to take CEntity* here..
            static_cast<CPed*>(creator)
        );
        break;
    }
    case eEntityType::ENTITY_TYPE_OBJECT: {
        static_cast<CObject*>(target)->m_pFire = this;
        break;
    }
    }

    active = true;
    createdByScript = false;
    makesNoise = true;
    beingExtinguished = false;
    firstGeneration = true;

    m_nNumGenerationsAllowed = nGens;
    m_fStrength = 1.0f;
    m_vecPosition = target->GetPosition();

    if (target->IsPed() && static_cast<CPed*>(target)->IsPlayer())
        m_nTimeToBurn = CTimer::GetTimeInMS() + 2333;
    else if (target->IsVehicle())
        m_nTimeToBurn = CTimer::GetTimeInMS() + CGeneral::GetRandomNumberInRange(0, 1000) + 3000;
    else
        m_nTimeToBurn = CTimer::GetTimeInMS() + CGeneral::GetRandomNumberInRange(0, 1000) + nTimeToBurn;

    SetTarget(target);
    SetCreator(creator);

    CreateFxSysForStrength(m_vecPosition, nullptr);
}

void CFire::Start(CVector pos, float fStrength, CEntity* target, uint8_t nGens) {
    SetTarget(target);
    SetCreator(nullptr);

    active = true;
    createdByScript = true;
    makesNoise = true;
    beingExtinguished = false;
    firstGeneration = true;

    m_nNumGenerationsAllowed = nGens;
    m_fStrength = fStrength;
    m_vecPosition = pos;

    if (target) {
        switch (target->m_nType) { /* Set target's `m_pFire` to `this` */
        case eEntityType::ENTITY_TYPE_PED:
            static_cast<CPed*>(target)->m_pFire = this;
            break;
        case eEntityType::ENTITY_TYPE_VEHICLE:
            static_cast<CVehicle*>(target)->m_pFire = this;
            break;
        }
    }

    CreateFxSysForStrength(target ? pos : target->GetPosition(), nullptr);
}

void CFire::CreateFxSysForStrength(const CVector& point, RwMatrixTag* matrix) {
    plugin::CallMethod<0x539360, CFire*, const CVector&, RwMatrixTag*>(this, point, matrix);
}

void CFire::Extinguish() {
    plugin::CallMethod<0x5393F0, CFire*>(this);
}

void CFire::ProcessFire() {
    plugin::CallMethod<0x53A570, CFire*>(this);
}

void CFire::DestroyFx() {
    if (m_pFxSystem) {
        g_fxMan.DestroyFxSystem(m_pFxSystem);   
        m_pFxSystem = nullptr;
    }
}

void CFire::SetTarget(CEntity* target) {
    if (m_pEntityTarget)
        m_pEntityTarget->CleanUpOldReference(&m_pEntityTarget); /* Assume old target's m_pFire is not pointing to `*this` */

    m_pEntityTarget = target; /* assign, even if its null, to clear it */
    if (target)
        m_pEntityTarget->RegisterReference(&m_pEntityTarget); /* Assume caller set target->m_pFire */
}

void CFire::SetCreator(CEntity* creator) {
    if (m_pEntityCreator)
        m_pEntityCreator->CleanUpOldReference(&m_pEntityCreator);

    m_pEntityCreator = creator; /* assign, even if its null, to clear it */
    if (creator)
        creator->RegisterReference(&m_pEntityCreator);
}
