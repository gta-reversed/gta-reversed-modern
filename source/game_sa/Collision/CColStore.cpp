#include "StdInc.h"

bool CColStore::LoadCol(int colId, unsigned char* data, int dataSize)
{
    return plugin::CallAndReturn<bool, 0x4106D0, int, unsigned char*, int>(colId, data, dataSize);
}

void CColStore::RemoveCol(int colNum)
{
    return plugin::Call<0x410730, int>(colNum);
}