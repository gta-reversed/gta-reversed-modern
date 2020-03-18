#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

auto OLD_CPhysical_ApplyCollisionAlt = (bool(__thiscall*) (CPhysical* pThis, CPhysical * pEntity, CColPoint * pColPoint, float* pDamageIntensity, CVector * pVecMoveSpeed, CVector * pVecTurnSpeed))0x544D50;
bool __fastcall CPhysical_ApplyCollisionAlt(CPhysical* pThis, void* padding, CPhysical* pEntity, CColPoint* pColPoint, float* pDamageIntensity, CVector* pVecMoveSpeed, CVector* pVecTurnSpeed);

void __cdecl HOOK_THEFUNCTION();

void InjectHooksMain(void)
{
    // CStreaming is unstable for now.
    //CStreaming::InjectHooks();

    CVehicleModelInfo::InjectHooks();
    CFileLoader::InjectHooks();
    CPhysical::InjectHooks();
    CRenderer::InjectHooks();
    CPed::InjectHooks();
    CPedIntelligence::InjectHooks();
    CTrain::InjectHooks();
    CTaskManager::InjectHooks();
    CTaskComplexUseSequence::InjectHooks();
    CTaskComplexSequence::InjectHooks();
    CTaskComplexWander::InjectHooks();
    CTaskComplexWanderCop::InjectHooks();
    CTaskSimplePlayerOnFoot::InjectHooks();
    CTaskSimpleSwim::InjectHooks();
    cBuoyancy::InjectHooks();
    CWanted::InjectHooks();
    CWeapon::InjectHooks();
    /*
     DetourRestoreAfterWith();
     DetourTransactionBegin();
     DetourUpdateThread(GetCurrentThread());

     std::printf("GOING TO HOOK FUNC NOW\n");
     DetourAttach(&(PVOID&)OLD_CPhysical_ApplyCollisionAlt, CPhysical_ApplyCollisionAlt);
     DetourTransactionCommit();
     */
}

bool __fastcall CPhysical_ApplyCollisionAlt(CPhysical* pThis, void* padding, CPhysical* pEntity, CColPoint* pColPoint, float* pDamageIntensity, CVector* pVecMoveSpeed, CVector* pVecTurnSpeed)
{
    printf("CPhysical_ApplyCollisionAlt called!\n");

    return true;
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
