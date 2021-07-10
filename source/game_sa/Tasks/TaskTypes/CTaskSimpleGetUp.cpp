#include "StdInc.h"

CColPoint(&CTaskSimpleGetUp::m_aColPoints)[32] = *reinterpret_cast<CColPoint(*)[32]>(0xC18F98);

void CTaskSimpleGetUp::InjectHooks()
{
    ReversibleHooks::Install("CTaskSimpleGetUp", "Constructor", 0x677F50, &CTaskSimpleGetUp::Constructor);
    ReversibleHooks::Install("CTaskSimpleGetUp", "StartAnim", 0x67C770, &CTaskSimpleGetUp::StartAnim);
    ReversibleHooks::Install("CTaskSimpleGetUp", "FinishGetUpAnimCB", 0x678110, &CTaskSimpleGetUp::FinishGetUpAnimCB);
    //VTABLE
    ReversibleHooks::Install("CTaskSimpleGetUp", "ProcessPed", 0x67FA80, &CTaskSimpleGetUp::ProcessPed_Reversed);
    ReversibleHooks::Install("CTaskSimpleGetUp", "MakeAbortable", 0x677FE0, &CTaskSimpleGetUp::MakeAbortable_Reversed);
}

CTaskSimpleGetUp* CTaskSimpleGetUp::Constructor()
{
    this->CTaskSimpleGetUp::CTaskSimpleGetUp();
    return this;
}

// 0x677F50
CTaskSimpleGetUp::CTaskSimpleGetUp()
{
    m_bIsFinished = false;
    m_bAnimFinished = false;
    m_pAnim = nullptr;
}

CTaskSimpleGetUp::~CTaskSimpleGetUp()
{
    if (m_pAnim)
        m_pAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
}

// 0x67FA80
bool CTaskSimpleGetUp::ProcessPed(CPed* ped)
{
    return ProcessPed_Reversed(ped);
}

// 0x677FE0
bool CTaskSimpleGetUp::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    return MakeAbortable_Reversed(ped, priority, _event);
}

bool CTaskSimpleGetUp::ProcessPed_Reversed(CPed* ped)
{
    ped->m_pedIK.bSlopePitch = true;

    if (m_bAnimFinished)
        return true;

    if (!m_pAnim)
        StartAnim(ped);

    if (m_pAnim)
        ped->bStuckUnderCar = false;

    if (!m_pAnim || m_pAnim->m_fCurrentTime < m_pAnim->m_pHierarchy->m_fTotalTime * 0.75F)
        ped->bFallenDown = true;

    return false;
}

bool CTaskSimpleGetUp::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event)
{

    if (priority == ABORT_PRIORITY_URGENT)
    {
        bool bTooMuchTimePassed = false;
        bool bFatalDamage = false;

        if (_event)
        {
            if (_event->GetEventType() == EVENT_DAMAGE)
            {
                auto eventDamage = reinterpret_cast<CEventDamage*>(_event);
                if (eventDamage->m_damageResponse.m_bHealthZero && eventDamage->m_bAddToEventGroup)
                    bFatalDamage = true;
                else if (CTimer::m_snTimeInMilliseconds - eventDamage->m_nStartTime > CTimer::GetTimeStepInMilliseconds() * 3.0F)
                    bTooMuchTimePassed = true;
            }
            else if (_event->GetEventPriority() < 61)
                return false;
        }

        if (m_pAnim && !bTooMuchTimePassed)
        {
            m_pAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
            m_pAnim = nullptr;
            m_bIsFinished = true;
            m_bAnimFinished = true;
        }
        else if (!m_bIsFinished && !bFatalDamage)
            return false;

        ped->bStuckUnderCar = false;
        return true;
    }

    if (priority == ABORT_PRIORITY_IMMEDIATE)
    {
        if (m_pAnim)
            m_pAnim->m_fBlendDelta = -1000.0F;
        ped->bStuckUnderCar = false;
        return true;
    }

    return false;
}

// 0x67C770
bool CTaskSimpleGetUp::StartAnim(CPed* ped)
{
    auto pVeh = CPedPlacement::IsPositionClearOfCars(ped);

    if (!pVeh
        || pVeh->m_vehicleType == VEHICLE_BIKE
        || pVeh->m_vehicleSubType == VEHICLE_QUAD
        || pVeh == ped->m_pAttachedTo
        || pVeh == ped->m_standingOnEntity
        )
    {
        auto pEntity = ped->m_pEntityIgnoredCollision;

        if (!pEntity
            || pEntity->m_nType != ENTITY_TYPE_VEHICLE
            || pEntity->AsVehicle()->m_vehicleType == VEHICLE_BIKE
            || pEntity->AsVehicle()->m_vehicleSubType == VEHICLE_QUAD
            || !IsVehiclePointerValid(pEntity->AsVehicle())
            || (ped->m_nRandomSeed + CTimer::m_FrameCounter - 3) % 8 == 0
            || CCollision::ProcessColModels(
                ped->GetMatrix(),
                *CModelInfo::GetModelInfo(ped->m_nModelIndex)->m_pColModel,
                pEntity->GetMatrix(),
                *CModelInfo::GetModelInfo(pEntity->m_nModelIndex)->m_pColModel,
                m_aColPoints,
                nullptr,
                nullptr,
                false
            ) <= 0
            )
        {
            ped->m_pEntityIgnoredCollision = nullptr;

            m_pAnim = CAnimManager::BlendAnimation(
                ped->m_pRwClump,
                ANIM_GROUP_DEFAULT,
                RpAnimBlendClumpGetFirstAssociation(ped->m_pRwClump, ANIM_FLAG_800) ? ANIM_ID_GETUP_FRONT : ANIM_ID_GETUP_0,
                1000.0F);

            m_pAnim->SetFinishCallback(FinishGetUpAnimCB, this);
            ped->SetPedState(PEDSTATE_IDLE);
            return true;
        }
    }

    ped->bStuckUnderCar = true;

    float fDamage;

    if (ped->IsPlayer())
    {
        if (CTimer::ms_fTimeStep > 0.0F)
            fDamage = CTimer::ms_fTimeStep;
        else
            return false;
    }
    else
    {
        if (CPad::GetPad(0)->DisablePlayerControls)
            fDamage = 1000.0F;
        else
            return false;
    }

    CPedDamageResponseCalculator damageResponseCalculator(pVeh, fDamage, WEAPON_RUNOVERBYCAR, PED_PIECE_TORSO, false);
    CEventDamage eventDamage(pVeh, CTimer::m_snTimeInMilliseconds, WEAPON_RUNOVERBYCAR, PED_PIECE_TORSO, 0, false, ped->bInVehicle);

    if (eventDamage.AffectsPed(ped))
        damageResponseCalculator.ComputeDamageResponse(ped, &eventDamage.m_damageResponse, true);
    else
        eventDamage.m_damageResponse.m_bDamageCalculated = true;

    ped->GetIntelligence()->m_eventGroup.Add(&eventDamage, false);

    return false;
}

// 0x678110
void CTaskSimpleGetUp::FinishGetUpAnimCB(CAnimBlendAssociation* pBlendAssoc, void* data)
{
    auto pTask = reinterpret_cast<CTaskSimpleGetUp*>(data);

    pTask->m_bIsFinished = true;
    pTask->m_bAnimFinished = true;
    pTask->m_pAnim->m_fBlendDelta = -1000.0F;
    pTask->m_pAnim = nullptr;
}
