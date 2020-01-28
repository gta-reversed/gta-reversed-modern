#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

//bool __thiscall CPhysical_ApplyFriction(CPhysical* pThis)
auto OLD_CPhysical_ApplyFriction = (bool(__thiscall*) (CPhysical * pThis, float fFriction, CColPoint * pColPoint))0x5454C0;
bool __fastcall CPhysical_ApplyFriction(CPhysical* pThis, void* padding, float fFriction, CColPoint* pColPoint);

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
    DetourAttach(&(PVOID&)OLD_CPhysical_ApplyFriction, CPhysical_ApplyFriction);
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

bool __fastcall CPhysical_ApplyFriction(CPhysical* pThis, void* padding, CPhysical* pEntity, float fFriction, CColPoint* pColPoint)
{
    printf(" calling CPhysical_ApplyFriction \n");

    return true;
}