#include "StdInc.h"

void CCoverPoint::ReleaseCoverPointForPed(CPed* ped) {
    plugin::CallMethod<0x698EF0>(this, ped);
}
