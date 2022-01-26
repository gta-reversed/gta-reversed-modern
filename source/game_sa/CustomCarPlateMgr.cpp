#include "StdInc.h"

void CCustomCarPlateMgr::InjectHooks() {
    RH_ScopedClass(CCustomCarPlateMgr);
    RH_ScopedCategoryRoot();

//    RH_ScopedInstall(Initialise, 0x6FD500);
//    RH_ScopedInstall(Shutdown, 0x6FD720);
}

// 0x6FD500
bool CCustomCarPlateMgr::Initialise() {
    return plugin::CallAndReturn<bool, 0x6FD500>();
}

// 0x6FD720
bool CCustomCarPlateMgr::Shutdown() {
    return plugin::CallAndReturn<bool, 0x6FD720>();
}


bool CCustomCarPlateMgr::GeneratePlateText(char* plateTextBuf, int32 length)
{
    return plugin::CallAndReturn<bool, 0x6FD5B0, char*, int32>(plateTextBuf, length);
}

RpMaterial* CCustomCarPlateMgr::SetupClump(RpClump* clump, char* plateText, uint8 plateType)
{
    return plugin::CallAndReturn<RpMaterial*, 0x6FE0F0, RpClump*, char*, uint8>(clump, plateText, plateType);
}
