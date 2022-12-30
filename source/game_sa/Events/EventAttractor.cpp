#include "StdInc.h"

#include "EventAttractor.h"

#include "IKChainManager_c.h"

void CEventAttractor::InjectHooks()
{
    RH_ScopedClass(CEventAttractor);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AF350);
    RH_ScopedVirtualInstall(AffectsPed, 0x4AF4B0);
    RH_ScopedVirtualInstall(CloneEditable, 0x4B7440);
    RH_ScopedInstall(IsEffectActive, 0x4AF460);
}

void CEventScriptedAttractor::InjectHooks()
{
    RH_ScopedClass(CEventScriptedAttractor);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x5FEF40);
}

CEventAttractor::CEventAttractor(C2dEffect* effect, CEntity* entity, bool bAvoidLookingAtAttractor)
{
    m_2dEffect = effect;
    m_entity   = entity;
    m_bAvoidLookingAtAttractor = bAvoidLookingAtAttractor;
    CEntity::SafeRegisterRef(m_entity);
}

CEventAttractor::~CEventAttractor()
{
    CEntity::SafeCleanUpRef(m_entity);
}

// 0x4AF350
CEventAttractor* CEventAttractor::Constructor(C2dEffect* effect, CEntity* entity, bool bAvoidLookingAtAttractor)
{
    this->CEventAttractor::CEventAttractor(effect, entity, bAvoidLookingAtAttractor);
    return this;
}

// 0x4AF4B0
bool CEventAttractor::AffectsPed(CPed* ped)
{
    return CEventAttractor::AffectsPed_Reversed(ped);
}

// 0x4B7440
CEventEditableResponse* CEventAttractor::CloneEditable()
{
    return CEventAttractor::CloneEditable_Reversed();
}

bool CEventAttractor::AffectsPed_Reversed(CPed* ped)
{
    if (ped->IsAlive()
        && (GetEventType() != EVENT_ATTRACTOR || m_entity)
        && (GetEventType() != EVENT_ATTRACTOR || IsEffectActive(m_entity, m_2dEffect))
        && !ped->GetIntelligence()->FindTaskByType(TASK_COMPLEX_BE_IN_COUPLE))
    {
        tEffectPedAttractor& pedAttractor = m_2dEffect->pedAttractor;
        if (ped->m_nPedType != PED_TYPE_COP
            || GetEventType() != EVENT_ATTRACTOR
            || !FindPlayerWanted()->m_nWantedLevel
            && pedAttractor.m_nAttractorType == PED_ATTRACTOR_TRIGGER_SCRIPT
            && CPopulation::PedMICanBeCreatedAtThisAttractor(ped->m_nModelIndex, pedAttractor.m_szScriptName))
        {
            CTask* activeTask = ped->GetTaskManager().GetActiveTask();
            if (!activeTask
                || m_bAvoidLookingAtAttractor
                ||
                activeTask->GetTaskType() != TASK_COMPLEX_USE_EFFECT
                && (pedAttractor.m_nAttractorType != PED_ATTRACTOR_SHELTER || CWeather::IsRainy()))
            {
                if (m_bAvoidLookingAtAttractor)
                    return true;
                if (CGeneral::GetRandomNumberInRange(0, 100) >= pedAttractor.m_nPedExistingProbability)
                    return false;
                if (CGeneral::GetRandomNumberInRange(0, 100) >= pedAttractor.field_36)
                    return true;
                if (!g_ikChainMan.IsLooking(ped)) {
                    uint32 time = CGeneral::GetRandomNumberInRange(2000, 4000);
                    CVector point = m_entity->GetMatrix() * m_2dEffect->m_vecPosn;
                    g_ikChainMan.LookAt("CEventAttractor", ped, 0, time, BONE_UNKNOWN, &point, false, 0.25f, 500, 3, false);
                }
            }     
        }
    }
    return false;
}

CEventEditableResponse* CEventAttractor::CloneEditable_Reversed()
{
    return new CEventAttractor(m_2dEffect, m_entity, m_bAvoidLookingAtAttractor);
}

// 0x4AF460
bool CEventAttractor::IsEffectActive(CEntity* entity, const C2dEffect* effect)
{
    auto modelInfo = CModelInfo::GetModelInfo(entity->m_nModelIndex);
    for (int32 i = 0; i < modelInfo->m_n2dfxCount; i++) {
        if (effect->m_nType == EFFECT_ATTRACTOR && effect == modelInfo->Get2dEffect(i))
            return true;
    }
    return false;
}

CEventScriptedAttractor::CEventScriptedAttractor(C2dEffect* the2dEffect, CEntity* entity, bool bAvoidLookingAtAttractor) :
    CEventAttractor(the2dEffect, entity, false)
{
}

CEventScriptedAttractor* CEventScriptedAttractor::Constructor(C2dEffect* the2dEffect, CEntity* entity, bool bAvoidLookingAtAttractor)
{
    this->CEventScriptedAttractor::CEventScriptedAttractor(the2dEffect, entity, bAvoidLookingAtAttractor);
    return this;
}
