#include "StdInc.h"

#include "EventInteriorUseInfo.h"
#include "Interior_c.h"
#include "InteriorInfo_t.h"

// 0x674EA0
CEventInteriorUseInfo::CEventInteriorUseInfo(InteriorInfo_t* interiorInfo, Interior_c* interior, uint32 animTime, int8 loopAction) : CEvent() {
    m_InteriorInfo = interiorInfo;
    m_nLoopAction = loopAction;
    m_Interior = interior;
    m_ActionAnimTime = animTime;
}

// 0x4B1640
bool CEventInteriorUseInfo::IsValid(CPed* ped) {
    if (ped)
        return ped->IsAlive();
    return CEvent::IsValid(ped);
}

// 0x674F80
bool CEventInteriorUseInfo::AffectsPed(CPed* ped) {
    return true;
}
