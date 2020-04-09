#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

auto OLD_CPhysical_ProcessEntityCollision = (int(__thiscall*) (CPhysical * pThis, CPhysical * entity, CColPoint * colpoint))0x546D00;
int __fastcall CPhysical_ProcessEntityCollision(CPhysical* pThis, void* padding, CPhysical* entity, CColPoint* colpoint);

void __cdecl HOOK_THEFUNCTION();

void InjectHooksMain(void)
{
    CStreaming::InjectHooks();
    CVehicleModelInfo::InjectHooks();
    CFileLoader::InjectHooks();
    CPhysical::InjectHooks();
    CRenderer::InjectHooks();
    CPed::InjectHooks();
    CPedIntelligence::InjectHooks();
    CTrain::InjectHooks();
    CEventEditableResponse::InjectHooks();
    CEventDamage::InjectHooks();
    CTaskManager::InjectHooks();
    CTaskComplexUseSequence::InjectHooks();
    CTaskComplexSequence::InjectHooks();
    CTaskComplexWander::InjectHooks();
    CTaskComplexWanderCop::InjectHooks();
    CTaskSimplePlayerOnFoot::InjectHooks();
    CTaskSimpleSwim::InjectHooks();
    CTaskSimpleHoldEntity::InjectHooks();
    CTaskSimplePutDownEntity::InjectHooks();
    CTaskSimplePickUpEntity::InjectHooks();
    cBuoyancy::InjectHooks();
    CWanted::InjectHooks();
    CWeapon::InjectHooks();
    CVehicle::InjectHooks();
    CPlayerPed::InjectHooks();
    CStats::InjectHooks();
    CCarCtrl::InjectHooks();
    CTheZones::InjectHooks();
    /*
     DetourRestoreAfterWith();
     DetourTransactionBegin();
     DetourUpdateThread(GetCurrentThread());

     std::printf("GOING TO HOOK FUNC NOW\n");
     DetourAttach(&(PVOID&)OLD_CPhysical_ProcessEntityCollision, CPhysical_ProcessEntityCollision);
     DetourTransactionCommit();
     */
}

int __fastcall CPhysical_ProcessEntityCollision(CPhysical* pThis, void* padding, CPhysical* entity, CColPoint* colpoint)
{
    printf("CPhysical_ProcessEntityCollision called!n");
    return 0;
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

DWORD RETURN_HOOK_INSIDE_IF = 0x0;
DWORD RETURN_HOOK_OUTSIDE_IF = 0x0554ADD;
DWORD RETURN_HOOK_EXIT_WITH_GRACE = 0x0;
void _declspec(naked) HOOK_THEFUNCTION()
{
    _asm
    {
    }
}
