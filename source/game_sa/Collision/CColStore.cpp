#include "StdInc.h"

std::int32_t CColStore::AddColSlot(const char* name)
{
    return plugin::CallAndReturn<std::int32_t, 0x411140, const char*>(name);
}

std::int32_t CColStore::FindColSlot()
{
    return plugin::CallAndReturn<std::int32_t, 0x410390>();
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
