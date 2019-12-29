#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

//bool __thiscall CTaskSimpleSwim_ProcessControlAI(CPhysical* pThis)
auto OLD_CTaskSimpleSwim_ProcessControlAI = (bool(__thiscall*) (CTaskSimpleSwim * pThis, void* padding, CPed * pPed))0x689640;
bool __fastcall CTaskSimpleSwim_ProcessControlAI(CTaskSimpleSwim* pThis, void* padding, CPed* pPed);

void __cdecl HOOK_THEFUNCTION();

void InjectHooksMain(void)
{
    /*CAnimManager::InjectHooks();
    pTaskManager->InjectHooks();
    std::printf("okay, only CAnimManager and CTaskManager hooks\n ");
    CStreaming::InjectHooks();
    CRenderer::InjectHooks();*/

    //HookInstall(0x54CFF0, &CPhysical::ProcessCollisionSectorList_SimpleCar, 5);

    /*
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CTaskSimpleSwim_ProcessControlAI, CTaskSimpleSwim_ProcessControlAI);
    DetourTransactionCommit();
   */
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


bool __fastcall CTaskSimpleSwim_ProcessControlAI(CTaskSimpleSwim* pThis, void* padding, CPed* pPed)
{
    printf(" calling CTaskSimpleSwim_ProcessControlAI \n");

    
    return true;
}
