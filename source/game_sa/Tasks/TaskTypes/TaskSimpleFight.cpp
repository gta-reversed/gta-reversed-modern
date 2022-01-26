#include "StdInc.h"

#include "TaskSimpleFight.h"

CMeleeInfo* CTaskSimpleFight::m_aComboData = (CMeleeInfo*)0xC170D0;

CTaskSimpleFight::CTaskSimpleFight(CEntity* entity, int32 nCommand, uint32 nIdlePeriod) : CTaskSimple() {
    plugin::CallMethod<0x61C470, CTaskSimpleFight*, CEntity*, int32, uint32>(this, entity, nCommand, nIdlePeriod);
}

// 0x6239D0
CTaskSimpleFight::~CTaskSimpleFight() {
    plugin::CallMethod<0x6239D0, CTaskSimpleFight*>(this);
}

bool CTaskSimpleFight::ControlFight(CEntity* entity, uint8 command) {
    return plugin::CallMethodAndReturn<bool, 0x61C5E0, CTaskSimpleFight*, CEntity*, uint8>(this, entity, command);
}

bool CTaskSimpleFight::IsComboSet() {
    return plugin::CallMethodAndReturn<bool, 0x4ABDC0, CTaskSimpleFight*>(this);
}

bool CTaskSimpleFight::IsHitComboSet() {
    return plugin::CallMethodAndReturn<bool, 0x4ABDF0, CTaskSimpleFight*>(this);
}

int32 CTaskSimpleFight::GetComboAnimGroupID() {
    return plugin::CallMethodAndReturn<int32, 0x4ABDA0, CTaskSimpleFight*>(this);
}

void CTaskSimpleFight::LoadMeleeData() {
    plugin::Call<0x5BEDC0>();
}

// 0x622E40
CTask* CTaskSimpleFight::Clone() {
    return new CTaskSimpleFight(m_pTargetEntity, m_nLastCommand, m_nIdlePeriod);
}

// 0x6239F0
bool CTaskSimpleFight::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x6239F0, CTaskSimpleFight*, CPed*, eAbortPriority, const CEvent*>(this, ped, priority, event);
}

// 0x629920
bool CTaskSimpleFight::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x629920, CTaskSimpleFight*, CPed*>(this, ped);
}

void CTaskSimpleFight::InjectHooks() {
    RH_ScopedClass(CTaskSimpleFight);
    RH_ScopedCategory("Tasks/TaskTypes");

}

CTaskSimpleFight* CTaskSimpleFight::Constructor(CEntity* entity, int32 nCommand, uint32 nIdlePeriod) {
    this->CTaskSimpleFight::CTaskSimpleFight(entity, nCommand, nIdlePeriod);
    return this;
}

CTaskSimpleFight* CTaskSimpleFight::Destructor() {
    this->CTaskSimpleFight::~CTaskSimpleFight();
    return this;
}
