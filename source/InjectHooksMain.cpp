#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

auto OLD_CPedIntelligence_FlushImmediately = (void(__thiscall*) (CPedIntelligence * pThis, bool bSetPrimaryDefaultTask))0x601640;
void __fastcall CPedIntelligence_FlushImmediately(CPedIntelligence* pThis, void* padding, bool bSetPrimaryDefaultTask);

void __cdecl HOOK_THEFUNCTION();

void InjectHooksMain(void)
{
    // CStreaming is unstable for now.
    //CStreaming::InjectHooks();

    ///*
    CPhysical::InjectHooks();
    CRenderer::InjectHooks();
    CPedIntelligence::InjectHooks();
    CTrain::InjectHooks();
    CTaskManager::InjectHooks();
    CTaskComplexUseSequence::InjectHooks();
    CTaskComplexSequence::InjectHooks();
    CTaskComplexWander::InjectHooks();
    CTaskComplexWanderCop::InjectHooks();
    CTaskSimplePlayerOnFoot::InjectHooks();
    CTaskSimpleSwim::InjectHooks();
    //*/
   /*
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CPedIntelligence_FlushImmediately, CPedIntelligence_FlushImmediately);
    DetourTransactionCommit();
     */
}

void __fastcall CPedIntelligence_FlushImmediately(CPedIntelligence* pThis, void* padding, bool bSetPrimaryDefaultTask)
{
}


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
    //FUNCTION_SWITCH_CASE_2 = 3,
    //FUNCTION_SOMELABEL = 4
};

DWORD RETURN_HOOK_INSIDE_IF = 0x060185A;
DWORD RETURN_HOOK_OUTSIDE_IF = 0x6018B1; //0x601748;
DWORD RETURN_HOOK_EXIT_WITH_GRACE = 0x601668;
void _declspec(naked) HOOK_THEFUNCTION()
{
    _asm
    {

    }
}
