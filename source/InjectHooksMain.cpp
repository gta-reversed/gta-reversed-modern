#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

//bool __thiscall CTaskSimpleHoldEntity_DropEntity(CTaskSimpleHoldEntity *this, struct CPed *ped)
auto OLD_CTaskSimpleHoldEntity_DropEntity = (bool(__thiscall*)(CTaskSimpleHoldEntity * pThis, CPed * pPed, bool bAddEventSoundQuiet))0x6930F0;
void __fastcall CTaskSimpleHoldEntity_DropEntity(CTaskSimpleHoldEntity* pThis, void* padding, CPed* pPed, bool bAddEventSoundQuiet);

void __cdecl HOOK_THEFUNCTION();

void InjectHooksMain(void)
{
    /*CAnimManager::InjectHooks();
    pTaskManager->InjectHooks();
    std::printf("okay, only CAnimManager and CTaskManager hooks\n ");
    CStreaming::InjectHooks();
    CRenderer::InjectHooks();*/

    //InjectHook(0x0681C10, &HOOK_THEFUNCTION, PATCH_JUMP);


   // /*
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CTaskSimpleHoldEntity_DropEntity, CTaskSimpleHoldEntity_DropEntity);
    DetourTransactionCommit();
    //*/
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


void __fastcall CTaskSimpleHoldEntity_DropEntity(CTaskSimpleHoldEntity* pThis, void* padding, CPed* pPed, bool bAddEventSoundQuiet)
{
    printf(" calling CTaskSimpleHoldEntity_DropEntity \n");
}
