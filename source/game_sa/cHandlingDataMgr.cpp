#include "StdInc.h"

cHandlingDataMgr& gHandlingDataMgr = *(cHandlingDataMgr*)0xC2B9C8;

tFlyingHandlingData* cHandlingDataMgr::GetFlyingPointer(unsigned char handlingId)
{
    return plugin::CallMethodAndReturn<tFlyingHandlingData*, 0x6F52D0, cHandlingDataMgr*, unsigned char>(this, handlingId);
}

tBoatHandlingData* cHandlingDataMgr::GetBoatPointer(unsigned char handlingId)
{
    return plugin::CallMethodAndReturn<tBoatHandlingData*, 0x6F5300, cHandlingDataMgr*, unsigned char>(this, handlingId);
}
