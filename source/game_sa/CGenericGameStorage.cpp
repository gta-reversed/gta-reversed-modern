#include "StdInc.h"

#include "CSimpleVariablesSaveStructure.h"

/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

bool CGenericGameStorage::LoadDataFromWorkBuffer(void* pData, int size) {
    return plugin::CallAndReturn<bool, 0x5D1300, void*, int>(pData, size);
}

bool CGenericGameStorage::SaveDataToWorkBuffer(void* pData, int Size) {
    return plugin::CallAndReturn<bool, 0x5D1270, void*, int>(pData, Size);
}

// 0x5D0F50
int CGenericGameStorage::GetCurrentVersionNumber() {
    return plugin::CallAndReturn<int, 0x5D0F50>();
}
