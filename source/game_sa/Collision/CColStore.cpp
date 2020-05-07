#include "StdInc.h"

CVector& CColStore::ms_vecCollisionNeeded = *(CVector*)0x965580;
bool& CColStore::ms_bCollisionNeeded = *(bool*)0x965558;

std::int32_t CColStore::AddColSlot(const char* name)
{
    return plugin::CallAndReturn<std::int32_t, 0x411140, const char*>(name);
}

void CColStore::AddCollisionNeededAtPosn(const CVector& pos)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::Call<0x4103A0, const CVector&>(pos);
#else
    ms_vecCollisionNeeded = pos;
    ms_bCollisionNeeded = true;
#endif
}

std::int32_t CColStore::FindColSlot()
{
    return plugin::CallAndReturn<std::int32_t, 0x410390>();
}

void CColStore::EnsureCollisionIsInMemory(CVector const& pos)
{
    return plugin::Call<0x410AD0, const CVector&>(pos);
}

bool CColStore::LoadCol(int colId, unsigned char* data, int dataSize)
{
    return plugin::CallAndReturn<bool, 0x4106D0, int, unsigned char*, int>(colId, data, dataSize);
}

void CColStore::LoadCollision(CVector point)
{
    return plugin::Call<0x410860, CVector>(point);
}

void CColStore::RemoveCol(int colNum)
{
    return plugin::Call<0x410730, int>(colNum);
}
