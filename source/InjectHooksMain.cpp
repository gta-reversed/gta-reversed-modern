#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

typedef int (__cdecl *hCRenderer_ScanSectorList)(unsigned int uiSector_x, unsigned int uiSector_y);
auto OLD_CRenderer_ScanSectorList = (hCRenderer_ScanSectorList)0x554840;
void __cdecl CRenderer_ScanSectorList(unsigned int uiSector_x, unsigned int uiSector_y);

void InjectHooksMain(void)
{
    /*CAnimManager::InjectHooks();
    CTaskManager::InjectHooks();
    std::printf("okay, only CAnimManager and CTaskManager hooks\n ");
    CStreaming::InjectHooks();
    CRenderer::InjectHooks();*/



    /*
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CRenderer_ScanSectorList, CRenderer_ScanSectorList);
    DetourTransactionCommit();*/
}