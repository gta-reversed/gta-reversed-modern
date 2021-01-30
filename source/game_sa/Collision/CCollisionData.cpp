#include "StdInc.h"

void CCollisionData::RemoveCollisionVolumes()
{
    plugin::CallMethod<0x40F070, CCollisionData*>(this);
}
