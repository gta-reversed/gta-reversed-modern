#include "StdInc.h"

void CCustomCarPlateMgr::InjectHooks() {
//    ReversibleHooks::Install("CCustomCarPlateMgr", "Initialise", 0x6FD500, &CCustomCarPlateMgr::Initialise);
//    ReversibleHooks::Install("CCustomCarPlateMgr", "Shutdown", 0x6FD720, &CCustomCarPlateMgr::Shutdown);
}

// 0x6FD500
bool CCustomCarPlateMgr::Initialise() {
    return plugin::CallAndReturn<bool, 0x6FD500>();
}

// 0x6FD720
bool CCustomCarPlateMgr::Shutdown() {
    return plugin::CallAndReturn<bool, 0x6FD720>();
}


bool CCustomCarPlateMgr::GeneratePlateText(char* plateTextBuf, int length)
{
    return plugin::CallAndReturn<bool, 0x6FD5B0, char*, int>(plateTextBuf, length);
}

RpMaterial* CCustomCarPlateMgr::SetupClump(RpClump* clump, char* plateText, unsigned char plateType)
{
    return plugin::CallAndReturn<RpMaterial*, 0x6FE0F0, RpClump*, char*, unsigned char>(clump, plateText, plateType);
}
