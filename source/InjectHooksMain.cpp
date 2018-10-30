#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

typedef signed int (__cdecl *hCRenderer_SetupMapEntityVisibility)(CEntity *pEntity, CBaseModelInfo *pBaseModelInfo, float fDistance, bool bIsTimeInRange);
auto OLD_CRenderer_SetupMapEntityVisibility = (hCRenderer_SetupMapEntityVisibility)0x553F60;
signed int __cdecl CRenderer_SetupMapEntityVisibility(CEntity *pEntity, CBaseModelInfo *pBaseModelInfo, float fDistance, bool bIsTimeInRange);

void InjectHooksMain(void)
{
    /*CAnimManager::InjectHooks();
    CTaskManager::InjectHooks();
    std::printf("okay, only CAnimManager and CTaskManager hooks\n ");
    CStreaming::InjectHooks();
    CRenderer::InjectHooks();*/


    //InjectHook(0x553F71, &HOOK_CRenderer_SetupMapEntityVisibility_1, PATCH_JUMP);

    /*
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CRenderer_SetupMapEntityVisibility, CRenderer_SetupMapEntityVisibility);
    DetourTransactionCommit();
    */
}

