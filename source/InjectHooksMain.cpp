#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

//bool __thiscall CPhysical_ProcessCollisionSectorList_SimpleCar(CPhysical* pThis)
auto OLD_CPhysical_ProcessCollisionSectorList_SimpleCar = (bool(__thiscall*) (CPhysical * pThis, void* padding, CPtrNodeDoubleLink * pNode))0x54CFF0;
bool __fastcall CPhysical_ProcessCollisionSectorList_SimpleCar(CPhysical* pThis, void* padding, CPtrNodeDoubleLink* pNode);

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
    DetourAttach(&(PVOID&)OLD_CPhysical_ProcessCollisionSectorList_SimpleCar, CPhysical_ProcessCollisionSectorList_SimpleCar);
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


bool __fastcall CPhysical_ProcessCollisionSectorList_SimpleCar(CPhysical* pThis, void* padding, CPtrNodeDoubleLink* pNode)
{
    printf(" calling CPhysical_ProcessCollisionSectorList_SimpleCar \n");
    return true;
}
