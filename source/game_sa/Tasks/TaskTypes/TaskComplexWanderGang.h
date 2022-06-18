#pragma

#include "TaskComplexWander.h"
#include "Ped.h"

class CTaskComplexWanderGang : public CTaskComplexWander {
public:
    uint32 m_nTime;
    int32  dword2C;
    int8   byte30;
    int8   byte31;
    int32  dword34;

public:
    CTaskComplexWanderGang(eMoveState moveState, uint8 dir, int a4, bool bWanderSensibly, float fTargetRadius);
    ~CTaskComplexWanderGang() override = default; // 0x66F650

    eWanderType GetWanderType() override { return WANDER_TYPE_GANG; } // 0x66F630
    void ScanForStuff(CPed* ped) override; // 0x66F640
    CTask* Clone() override { return new CTaskComplexWanderGang(m_nMoveState, m_nDir, dword34, m_nFlags & 1, 0.5); } // 0x671470
};
VALIDATE_SIZE(CTaskComplexWanderGang, 0x38);
