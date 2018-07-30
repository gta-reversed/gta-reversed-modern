#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

typedef void(__cdecl *hCRenderer_AddEntityToRenderList)( CEntity *pEntity, float fDistance );
auto OLD_CRenderer_AddEntityToRenderList = (hCRenderer_AddEntityToRenderList)0x05534B0;
void __cdecl CRenderer_AddEntityToRenderList(CEntity *pEntity, float fDistance);

void InjectHooksMain(void)
{
    CAnimManager::InjectHooks();
    CTaskManager::InjectHooks();
    CStreaming::InjectHooks();
    CRenderer::InjectHooks();

    /*DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CRenderer_AddEntityToRenderList, CRenderer_AddEntityToRenderList);

    DetourTransactionCommit(); */
    
}