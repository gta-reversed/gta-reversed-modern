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

bool cHandlingDataMgr::HasFrontWheelDrive(unsigned char handlingId)
{
    return ((bool(__thiscall*)(cHandlingDataMgr*, unsigned char))0x6A0480)(this, handlingId);
};

bool cHandlingDataMgr::HasRearWheelDrive(unsigned char handlingId)
{
    return ((bool(__thiscall*)(cHandlingDataMgr*, unsigned char))0x6A04B0)(this, handlingId);
};
