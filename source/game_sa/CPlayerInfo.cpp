#include "StdInc.h"

void CPlayerInfo::InjectHooks() {
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
