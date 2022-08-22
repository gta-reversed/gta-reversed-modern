#include "StdInc.h"

#include "TaskSimpleSay.h"

// 0x48E360
CTaskSimpleSay::CTaskSimpleSay(uint32 sayId, uint32 sayDuration) :
    CTaskSimple(),
    m_SayId{ sayId },
    m_SayDuration{ sayDuration }
{
}

// 0x48E440
bool CTaskSimpleSay::ProcessPed(CPed* ped) {
    m_Timer.StartIfNotAlready(m_SayDuration);
    ped->Say(m_SayId);
    return m_Timer.IsOutOfTime();
}
