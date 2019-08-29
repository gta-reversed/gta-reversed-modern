#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")


auto OLD_CPedIntelligence_FlushImmediately = (void (__thiscall*)(CPedIntelligence *pThis, char bSetPrimaryDefaultTask))0x601640;
//auto OLD_CPedIntelligence_FlushIntelligence = (void (__thiscall*)(CPedIntelligence *pThis))0x0;
//auto OLD_CPedIntelligence_GetEffectInUse = (int (__thiscall*)(CPedIntelligence *pThis))0x0;
//auto OLD_CPedIntelligence_GetMoveStateFromGoToTask = (int (__thiscall*)(CPedIntelligence *pThis))0x0;
//auto OLD_CPedIntelligence_GetTaskClimb = (CTask *(__thiscall*)(CPedIntelligence *pThis);
//auto OLD_CPedIntelligence_GetTaskDuck = (CTask *(__thiscall*)(CPedIntelligence *pThis, char IgnoreCheckingForSimplestActiveTask))0x0;
//auto OLD_CPedIntelligence_GetTaskFighting = (CTaskSimpleFight *(__thiscall*)(CPedIntelligence *pThis))0x0;
//auto OLD_CPedIntelligence_GetTaskHold = (CTaskSimpleHoldEntity *(__thiscall*)(CPedIntelligence *pThis, char IgnoreCheckingForSimplestActiveTask))0x0;
//auto OLD_CPedIntelligence_GetTaskInAir = (CTask *(__thiscall*)(CPedIntelligence *pThis))0x0;
//auto OLD_CPedIntelligence_GetTaskJetPack = (CTask *(__thiscall*)(CPedIntelligence *pThis))0x0;
//auto OLD_CPedIntelligence_GetTaskSwim = (CTask *(__thiscall*)(CPedIntelligence *pThis))0x0;
//auto OLD_CPedIntelligence_GetTaskThrow = (CTask *(__thiscall*)(CPedIntelligence *pThis))0x0;
//auto OLD_CPedIntelligence_GetTaskUseGun = (CTaskSimpleUseGun *(__thiscall*)(CPedIntelligence *pThis))0x0;
//auto OLD_CPedIntelligence_GetUsingParachute = (bool (__thiscall*)(CPedIntelligence *pThis))0x0;
//auto OLD_CPedIntelligence_IsFriendlyWith = (bool (__thiscall*)(CPedIntelligence *pThis, CPed *pPed))0x0;
//auto OLD_CPedIntelligence_IsInSeeingRange = (bool (__thiscall*)(CPedIntelligence *pThis, CVector *pPosition))0x0;
//auto OLD_CPedIntelligence_IsInterestingEntity = (bool (__thiscall*)(CPedIntelligence *pThis, CEntity *pEntity))0x0;

void __fastcall CPedIntelligence_FlushImmediately(CPedIntelligence* pThis, void* padding, bool bSetPrimaryDefaultTask);

void __cdecl HOOK_THEFUNCTION();

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
    DetourAttach(&(PVOID&)OLD_CPedIntelligence_FlushImmediately, CPedIntelligence_FlushImmediately);
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


void __fastcall CPedIntelligence_FlushImmediately(CPedIntelligence* pThis, void* padding, bool bSetPrimaryDefaultTask)
{
    printf(" calling CPedIntelligence_FlushImmediately\n");

 
}