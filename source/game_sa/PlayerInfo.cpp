#include "StdInc.h"

void CPlayerInfo::InjectHooks()
{
    ReversibleHooks::Install("CPlayerInfo", "IsPlayerInRemoteMode", 0x56DAB0, &CPlayerInfo::IsPlayerInRemoteMode);
}

bool CPlayerInfo::IsPlayerInRemoteMode()
{
    //plugin::CallMethod<0x56DAB0, CPlayerInfo*>(this);
    return m_pRemoteVehicle != nullptr;
}

void CPlayerInfo::Load() {
    plugin::CallMethod<0x5D3B00>(this);
}

// 0x56F7D0
void CPlayerInfo::LoadPlayerSkin() {
    plugin::CallMethod<0x56F7D0, CPlayerInfo*>(this);
}

// 0x56F330
void CPlayerInfo::Clear() {
    plugin::CallMethod<0x56F330, CPlayerInfo*>(this);
}

void CPlayerInfo::DeletePlayerSkin() {
    plugin::CallMethod<0x56EA80, CPlayerInfo*>(this);
}
