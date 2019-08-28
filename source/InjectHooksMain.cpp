#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")


//void PlayIdleAnimations(CPed* pPed)
auto OLD_CTaskSimplePlayerOnFoot_ProcessPlayerWeapon = (void(__thiscall*)(CTaskSimplePlayerOnFoot * pThis, CPed * pPed))0x6859A0;

void __fastcall CTaskSimplePlayerOnFoot_ProcessPlayerWeapon(CTaskSimplePlayerOnFoot* pThis, void* padding, CPlayerPed* pPlayerPed);

//CTask* __cdecl CTaskManager__GetSimplestTask(CTask* pTask);
void __cdecl HOOK_THEFUNCTION();

#include <ctime>
void InjectHooksMain(void)
{
    /*CAnimManager::InjectHooks();
    pTaskManager->InjectHooks();
    std::printf("okay, only CAnimManager and CTaskManager hooks\n ");
    CStreaming::InjectHooks();
    CRenderer::InjectHooks();*/

    //InjectHook(0x0681C10, &HOOK_THEFUNCTION, PATCH_JUMP);


        /*
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CTaskSimplePlayerOnFoot_ProcessPlayerWeapon, CTaskSimplePlayerOnFoot_ProcessPlayerWeapon);
    DetourTransactionCommit();
     */
    /**/
}
/*
enum eFunctionReturnValue
{
    FUNCTION_RETURN = 0,
    FUNCTION_INSIDE_IF = 1,
    FUNCTION_OUTSIDE_IF = 2
}; 
*/
/*
dwReturnLocation:
0 means that the function should return.
1 means continue the function and it is inside of the "if" condition
2 means continue the function and it is outside of the "if" condition
*/

enum eFunctionReturnValue
{
    FUNCTION_RETURN = 0,
    FUNCTION_INSIDE_IF = 1,
    FUNCTION_OUTSIDE_IF = 2,
    FUNCTION_SWITCH_CASE_2 = 3,
    FUNCTION_SOMELABEL = 4
};

void __fastcall CTaskSimplePlayerOnFoot_ProcessPlayerWeapon(CTaskSimplePlayerOnFoot* pThis, void* padding, CPlayerPed* pPlayerPed)
{
    printf(" calling CTaskSimplePlayerOnFoot__ProcessPlayerWeapon\n");

  
}
