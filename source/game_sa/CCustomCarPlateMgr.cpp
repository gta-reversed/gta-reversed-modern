#include "StdInc.h"

bool CCustomCarPlateMgr::GeneratePlateText(char* plateTextBuf, int length)
{
    return plugin::CallAndReturn<bool, 0x6FD5B0, char*, int>(plateTextBuf, length);
}

RpMaterial* CCustomCarPlateMgr::SetupClump(RpClump* clump, char* plateText, unsigned char plateType)
{
    return plugin::CallAndReturn<RpMaterial*, 0x6FE0F0, RpClump*, char*, unsigned char>(clump, plateText, plateType);
}
