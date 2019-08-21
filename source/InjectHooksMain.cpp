#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")


//void PlayIdleAnimations(CPed* pPed)
auto OLD_CTaskSimplePlayerOnFoot_PlayIdleAnimations = (void(__thiscall*)(CTaskSimplePlayerOnFoot * pThis, CPed * pPed))0x6872C0;

void __fastcall CTaskSimplePlayerOnFoot_PlayIdleAnimations(CTaskSimplePlayerOnFoot* pThis, void* padding, CPed* pPed);

//CTask* __cdecl CTaskManager__GetSimplestTask(CTask* pTask);
void __cdecl HOOK_THEFUNCTION();

void InjectHooksMain(void)
{
    /*CAnimManager::InjectHooks();
    CTaskManager::InjectHooks();
    std::printf("okay, only CAnimManager and CTaskManager hooks\n ");
    CStreaming::InjectHooks();
    CRenderer::InjectHooks();*/


    //InjectHook(0x0681C10, &HOOK_THEFUNCTION, PATCH_JUMP);

   /*
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CTaskSimplePlayerOnFoot_PlayIdleAnimations, CTaskSimplePlayerOnFoot_PlayIdleAnimations);
    DetourTransactionCommit();
    */
}

enum eFunctionReturnValue 
{
    FUNCTION_RETURN = 0,
    FUNCTION_INSIDE_IF = 1,
    FUNCTION_OUTSIDE_IF = 2
};
/*
dwReturnLocation:
0 means that the function should return.
1 means continue the function and it is inside of the "if" condition
2 means continue the function and it is outside of the "if" condition
*/

void __fastcall CTaskSimplePlayerOnFoot_PlayIdleAnimations(CTaskSimplePlayerOnFoot* pThis, void* padding, CPed* pPed)
//CTask* __cdecl CTaskManager__GetSimplestTask(CTask* pTask)
{
    //printf("CTaskSimplePlayerOnFoot_PlayIdleAnimations called\n");



}
