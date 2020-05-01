#include "StdInc.h"

/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

bool CGenericGameStorage::LoadDataFromWorkBuffer(void* pData, int size) {
    return plugin::CallAndReturnDynGlobal<bool, void*, int>(0x5D1300, pData, size);
}

bool CGenericGameStorage::SaveDataToWorkBuffer(void* pData, int Size) {
    return plugin::CallAndReturnDynGlobal<bool, void*, int>(0x5D1270, pData, Size);
}