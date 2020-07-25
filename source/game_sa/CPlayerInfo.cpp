#include "StdInc.h"

void CPlayerInfo::DeletePlayerSkin()
{
    plugin::CallMethod<0x56EA80, CPlayerInfo*>(this);
}
