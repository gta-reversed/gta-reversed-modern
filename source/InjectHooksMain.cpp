#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")
    
typedef void(__thiscall*  hCTaskSimpleSwim__ProcessSwimAnims)
(
    CTaskSimpleSwim * pThis, CPed *pPed
);
auto OLD_CTaskSimpleSwim__ProcessSwimAnims = (hCTaskSimpleSwim__ProcessSwimAnims)0x6899F0;

void __fastcall CTaskSimpleSwim__ProcessSwimAnims(CTaskSimpleSwim * pThis, void* padding, CPed *pPed);



void InjectHooksMain(void)
{
    CAnimManager::InjectHooks();
    CTaskManager::InjectHooks();
    CStreaming::InjectHooks();

   /* DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CTaskSimpleSwim__ProcessSwimAnims, CTaskSimpleSwim__ProcessSwimAnims);

    DetourTransactionCommit(); */
   
}
