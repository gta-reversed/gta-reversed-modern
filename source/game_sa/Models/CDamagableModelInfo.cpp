#include "StdInc.h"

void CDamagableModelInfo::SetDamagedAtomic(RpAtomic* atomic)
{
    plugin::CallMethod<0x4C48D0, CDamagableModelInfo*, RpAtomic*>(this, atomic);
}