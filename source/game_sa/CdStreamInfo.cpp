#include "StdInc.h"

int __cdecl CdStreamSync(DWORD streamNum)
{
    typedef int (__cdecl* hCdStreamSync)( DWORD streamNum );
    hCdStreamSync _CdStreamSync = (hCdStreamSync)0x406460;
    return _CdStreamSync(streamNum);
}

int __cdecl CdStreamGetStatus(int streamNum)
{
    typedef int(__cdecl* hCdStreamGetStatus)(DWORD streamNum);
    hCdStreamGetStatus _CdStreamGetStatus = (hCdStreamGetStatus)0x1563850;
    return _CdStreamGetStatus(streamNum);
}