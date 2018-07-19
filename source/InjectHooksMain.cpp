#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

typedef void(__thiscall*  hCTaskSimpleSwim__ProcessPed)
(
    CTaskSimpleSwim * pThis, CPed *pPed
);
auto OLD_CTaskSimpleSwim__ProcessPed = (hCTaskSimpleSwim__ProcessPed)0x68B1C0;

bool __fastcall CTaskSimpleSwim__ProcessPed(CTaskSimpleSwim * pThis, void* padding, CPed *pPed);



void InjectHooksMain(void)
{
   CAnimManager::InjectHooks();
   CTaskManager::InjectHooks();
   //CStreaming::InjectHooks();


    
    /*DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CTaskSimpleSwim__ProcessPed, CTaskSimpleSwim__ProcessPed);

    DetourTransactionCommit(); */
    
}