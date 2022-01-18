#include "StdInc.h"

#include "SimpleVariablesSaveStructure.h"

/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

bool CGenericGameStorage::LoadDataFromWorkBuffer(void* pData, int32 size) {
    return plugin::CallAndReturn<bool, 0x5D1300, void*, int32>(pData, size);
}

bool CGenericGameStorage::SaveDataToWorkBuffer(void* pData, int32 Size) {
    return plugin::CallAndReturn<bool, 0x5D1270, void*, int32>(pData, Size);
}

// 0x5D0F50
int32 CGenericGameStorage::GetCurrentVersionNumber() {
    return plugin::CallAndReturn<int32, 0x5D0F50>();
}
