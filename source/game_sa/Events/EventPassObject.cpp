#include "StdInc.h"

#include "EventPassObject.h"

void CEventPassObject::InjectHooks() {
    RH_ScopedClass(CEventPassObject);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x65DC70);
    RH_ScopedVirtualInstall(IsValid, 0x4B1700);
}

CEventPassObject* CEventPassObject::Constructor(CEntity* giver, bool dontPassObject) { this->CEventPassObject::CEventPassObject(giver, dontPassObject); return this; }
bool CEventPassObject::IsValid(CPed* ped) { return CEventPassObject::IsValid_Reversed(ped); }

// 0x65DC70
CEventPassObject::CEventPassObject(CEntity* giver, bool dontPassObject) : CEvent() {
    m_giver = giver;
    CEntity::SafeRegisterRef(m_giver);
    m_dontPassObject = dontPassObject;
}

// 0x65DCF0
CEventPassObject::~CEventPassObject() {
    CEntity::SafeCleanUpRef(m_giver);
}

// 0x4B1700
bool CEventPassObject::IsValid_Reversed(CPed* ped) {
    if (ped)
        return ped->IsAlive();

    if (CEvent::IsValid(ped))
        return true;

    return false;
}
