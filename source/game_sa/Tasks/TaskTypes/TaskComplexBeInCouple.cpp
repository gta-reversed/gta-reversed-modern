#include "StdInc.h"

#include "TaskComplexBeInCouple.h"
#include "TaskComplexWanderStandard.h"
#include "IKChainManager_c.h"

// 0x6836F0
CTaskComplexBeInCouple::CTaskComplexBeInCouple(CPed* ped, bool a3, bool a4, bool a5, float a6) : CTaskComplex() {
    byte14 = a3;
    byte15 = a4;
    m_Ped = ped;
    byte16 = a5;
    float18 = a6;
    byte1C = 0;
    CEntity::SafeRegisterRef(m_Ped);
}

// 0x683780
CTaskComplexBeInCouple::~CTaskComplexBeInCouple() {
    CEntity::SafeCleanUpRef(m_Ped);
}

// 0x6837E0
CTask* CTaskComplexBeInCouple::CreateFirstSubTask(CPed* ped) {
    return CreateNextSubTask(ped);
}

// 0x6837F0
void CTaskComplexBeInCouple::AbortArmIK(CPed* ped) {
    if (IKChainManager_c::IsArmPointing(0, ped)) {
        IKChainManager_c::AbortPointArm(0, ped, 250);
    }

    if (IKChainManager_c::IsArmPointing(1, ped)) {
        IKChainManager_c::AbortPointArm(1, ped, 250);
    }
}

// 0x6847C0
bool CTaskComplexBeInCouple::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    if (m_Ped && event && event->HasEditableResponse()) {
        auto editable = static_cast<CEventEditableResponse*>(const_cast<CEvent*>(event)); // Okay let's go!

        bool bAddToEventGroup = editable->m_bAddToEventGroup;
        editable->m_bAddToEventGroup = false;
        switch (event->GetEventType()) {
        case EVENT_DAMAGE:
        case EVENT_GUN_AIMED_AT:
        case EVENT_SHOT_FIRED:
            m_Ped->GetEventGroup().Add(editable, false);
            break;
        }
        editable->m_bAddToEventGroup = bAddToEventGroup;
    }
    AbortArmIK(ped);
    return true;
}

// 0x684840
CTask* CTaskComplexBeInCouple::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x684840, CTaskComplexBeInCouple*, CPed*>(this, ped);

    if (!m_Ped) {
        AbortArmIK(ped);
        return nullptr;
    }

    if (this->byte14) {
        AbortArmIK(ped);
        return new CTaskComplexWanderStandard(4, CGeneral::GetRandomNumberInRange(0, 8), true);
    } else {
        AbortArmIK(ped);
        // todo: return new CTaskComplexWalkAlongsidePed(m_Ped, float18);
    }
}

// 0x684930
CTask* CTaskComplexBeInCouple::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x684930, CTaskComplexBeInCouple*, CPed*>(this, ped);
}
