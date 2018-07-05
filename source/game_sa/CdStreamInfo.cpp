#include "StdInc.h"

int __cdecl CdStreamSync(DWORD streamNum)
{
    typedef int (__cdecl* hCdStreamSync)( DWORD streamNum );
    hCdStreamSync _CdStreamSync = (hCdStreamSync)0x406460;
    return _CdStreamSync(streamNum);
}