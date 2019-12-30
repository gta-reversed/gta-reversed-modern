#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

//bool __thiscall CTaskSimpleSwim_ProcessSwimmingResistance(CPhysical* pThis)
auto OLD_CTaskSimpleSwim_ProcessSwimmingResistance = (void(__thiscall*) (CTaskSimpleSwim * pThis, CPed * pPed))0x68A1D0;
void __fastcall CTaskSimpleSwim_ProcessSwimmingResistance(CTaskSimpleSwim* pThis, void* padding, CPed* pPed);

void __cdecl HOOK_THEFUNCTION();

void InjectHooksMain(void)
{
    /*CAnimManager::InjectHooks();
    pTaskManager->InjectHooks();
    std::printf("okay, only CAnimManager and CTaskManager hooks\n ");
    CStreaming::InjectHooks();
    CRenderer::InjectHooks();*/

   // HookInstall(0x68A1D0, &CTaskSimpleSwim::ProcessSwimmingResistance, 7);

  /*
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CTaskSimpleSwim_ProcessSwimmingResistance, CTaskSimpleSwim_ProcessSwimmingResistance);
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

void __fastcall CTaskSimpleSwim_ProcessSwimmingResistance(CTaskSimpleSwim* pThis, void* padding, CPed* pPed)
{
    printf(" calling CTaskSimpleSwim_ProcessSwimmingResistance \n");

  
}
