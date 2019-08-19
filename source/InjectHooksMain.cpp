#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")
//auto _rwStreamWriteVersionedChunkHeader = (RwStream * (__cdecl*)(RwStream * stream, int type, int size, int version, unsigned __int16 buildNum))0x7ED270;

auto OLD_CTaskManager_ManageTasks = (void (__thiscall*)(CTaskManager*pThis))0x681C10;
void __fastcall CTaskManager_ManageTasks(CTaskManager* pThis, void* padding);

void __cdecl HOOK_THEFUNCTION();

void InjectHooksMain(void)
{
    /*CAnimManager::InjectHooks();
    CTaskManager::InjectHooks();
    std::printf("okay, only CAnimManager and CTaskManager hooks\n ");
    CStreaming::InjectHooks();
    CRenderer::InjectHooks();*/


    //InjectHook(0x0681C10, &HOOK_THEFUNCTION, PATCH_JUMP);

   ///*
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CTaskManager_ManageTasks, CTaskManager_ManageTasks);
    DetourTransactionCommit();
    //*/
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

void __fastcall CTaskManager_ManageTasks(CTaskManager* pThis, void* padding)
{
}
