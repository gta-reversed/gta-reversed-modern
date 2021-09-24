#include "StdInc.h"

#include "CTaskComplexPartner.h"

void CTaskComplexPartner::InjectHooks() {
    ReversibleHooks::Install("CTaskComplexPartner", "CTaskComplexPartner", 0x681E70, &CTaskComplexPartner::Constructor);
}

// 0x681E70
CTaskComplexPartner::CTaskComplexPartner(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, bool makePedAlwaysFacePartner, int8 updateDirectionCount, CVector point)
    : CTaskComplex()
{
    m_leadSpeaker              = leadSpeaker;
    m_makePedAlwaysFacePartner = makePedAlwaysFacePartner;
    m_distanceMultiplier       = distanceMultiplier;
    m_updateDirectionCount     = updateDirectionCount;
    m_point                    = point;
    m_partner                  = partner;
    m_partnerState             = PARTNER_STATE_UNK_1;
    m_taskCompleted            = false;
    m_firstToTargetFlag        = -1;
    m_requiredAnimsStreamedIn  = false;
    m_animBlockName[0]         = '\0';

    if (partner)
        partner->RegisterReference(reinterpret_cast<CEntity**>(&m_partner));
}

CTaskComplexPartner::~CTaskComplexPartner() {
    if (m_partner)
        m_partner->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_partner));
    if (m_requiredAnimsStreamedIn) {
        if (memcmp(m_animBlockName, gta_empty_string, 1u))
            CAnimManager::RemoveAnimBlockRef(CAnimManager::GetAnimationBlockIndex(m_animBlockName));
        m_requiredAnimsStreamedIn = false;
    }
}

CTaskComplexPartner* CTaskComplexPartner::Constructor(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, bool makePedAlwaysFacePartner, int8 updateDirectionCount, CVector point) {
    this->CTaskComplexPartner::CTaskComplexPartner(commandName, partner, leadSpeaker, distanceMultiplier, makePedAlwaysFacePartner, updateDirectionCount, point);
    return this;
}

CTask* CTaskComplexPartner::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x683AD0, CTask*, CPed*>(this, ped);
}

CTask* CTaskComplexPartner::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x681F20, CTask*, CPed*>(this, ped);
}

CTask* CTaskComplexPartner::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6840D0, CTask*, CPed*>(this, ped);
}

void CTaskComplexPartner::StreamRequiredAnims() {
    return plugin::CallMethod<0x682310, CTask*>(this);
}

void CTaskComplexPartner::RemoveStreamedAnims() {
    return plugin::CallMethod<0x682370, CTask*>(this);
}
