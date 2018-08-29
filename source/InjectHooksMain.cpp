#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

typedef signed int(__cdecl *hCRenderer_SetupEntityVisibility)(CEntity *pEntity, float *outDistance);
auto OLD_CRenderer_SetupEntityVisibility = (hCRenderer_SetupEntityVisibility)0x554230;
signed int __cdecl CRenderer_SetupEntityVisibility(CEntity *pEntity, float *outDistance);


void InjectHooksMain(void)
{
    //CAnimManager::InjectHooks();
   // CTaskManager::InjectHooks();
    //std::printf("okay, only CAnimManager and CTaskManager hooks\n ");
    //CStreaming::InjectHooks();
    CRenderer::InjectHooks();

    /*DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CRenderer_SetupEntityVisibility, CRenderer_SetupEntityVisibility);
    DetourTransactionCommit();*/  
}
