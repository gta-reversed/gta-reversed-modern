#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

//auto OLD_CTaskManager_ManageTasks = (void (__thiscall*)(CTaskManager*pThis))0x681C10;
//auto OLD_CTaskManager__GetActiveTask = (CTask *(__thiscall*)(CTaskManager *pThis))0x681720;
//auto OLD_CTaskManager__FindActiveTaskByType = (CTask *(__thiscall*) (CTaskManager *pThis, int taskId))0x681740;
//auto OLD_CTaskManager__FindTaskByType = (CTask *(__thiscall*)(CTaskManager *pThis, int tasksId, int taskId))0x6817D0;
//auto OLD_CTaskManager__GetTaskSecondary = (int (__thiscall*)(CTaskManager *pThis, int taskId))0x0;
//auto OLD_CTaskManager__HasTaskSecondary = (char (__thiscall*)(CTaskManager *pThis, CTask *task))0x681820;
//auto OLD_CTaskManager__Flush = (void (__thiscall*) (CTaskManager *pThis))0x681850;
//auto OLD_CTaskManager__FlushImmediately =  (void (__thiscall*)(CTaskManager* pThis))0x6818A0;
//auto OLD_CTaskManager__SetNextSubTask = (void (__thiscall*) (CTaskManager *a1, CTask *a2))0x681920;
//auto OLD_CTaskManager__GetSimplestTask = (CTask* (*__cdecl) (CTask *a1))0x681970;
//auto OLD_CTaskManager__StopTimers = (int (__thiscall*)(CTaskManager *pThis, CEvent *a2))0x6819A0;
//auto OLD_CTaskManager__GetSimplestActiveTask = (CTask *(__thiscall*)(CTaskManager *pThis))0x6819D0;
//auto OLD_CTaskManager__GetSimplestTask_taskId = (CTask *(__thiscall*) (CTaskManager *pThis, int tasksId))0x681A00;
//auto OLD_CTaskManager__AddSubTasks = (void (__thiscall*)(CTaskManager *pThis, CTaskComplex *task))0x681A30;
//auto OLD_CTaskManager__ParentsControlChildren = (void (__thiscall*)(CTaskManager *pThis, CTask *a2))0x681A80;
//auto OLD_CTaskManager__SetTask = (void (__thiscall*) (CTaskManager *pThis, CTask *task, int tasksId, int a4))0x681AF0;
//auto OLD_CTaskManager__SetTaskSecondary = (void (__thiscall*) (void *pThis, CTaskComplex *task, int a3))0x681B60;
auto OLD_CTaskManager__ClearTaskEventResponse = (CTask* (__thiscall*)(CTaskManager *pThis))0x681BD0;

void __fastcall CTaskManager__ClearTaskEventResponse(CTaskManager* pThis, void* padding);
//CTask* __cdecl CTaskManager__GetSimplestTask(CTask* pTask);
void __cdecl HOOK_THEFUNCTION();

void InjectHooksMain(void)
{
    /*CAnimManager::InjectHooks();
    CTaskManager::InjectHooks();
    std::printf("okay, only CAnimManager and CTaskManager hooks\n ");
    CStreaming::InjectHooks();
    CRenderer::InjectHooks();*/


    //InjectHook(0x0681C10, &HOOK_THEFUNCTION, PATCH_JUMP);

   /*
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CTaskManager__ClearTaskEventResponse, CTaskManager__ClearTaskEventResponse);
    DetourTransactionCommit();
    */
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

void __fastcall CTaskManager__ClearTaskEventResponse(CTaskManager* pThis, void* padding)
//CTask* __cdecl CTaskManager__GetSimplestTask(CTask* pTask)
{
    printf("CTaskManager__ClearTaskEventResponse called\n");

}
