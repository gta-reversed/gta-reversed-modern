#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")


typedef void (__cdecl*  hCStreaming__LoadAllRequestedModels)
(
    bool bOnlyPriorityRequests
);

hCStreaming__LoadAllRequestedModels OLD_CStreaming__LoadAllRequestedModels = (hCStreaming__LoadAllRequestedModels)0x40A45E;

void __cdecl CStreaming__LoadAllRequestedModels(bool bOnlyPriorityRequests);

void InjectHooksMain(void)
{
    InjectHook(0x15674C0, &CStreamingInfo::AddToList, PATCH_JUMP);
    InjectHook(0x40A45E, &CStreaming::LoadAllRequestedModels, PATCH_JUMP);
    InjectHook(0x4087E0, &CStreaming::RequestModel, PATCH_JUMP);
   
    /*DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CStreaming__LoadAllRequestedModels, CStreaming__LoadAllRequestedModels);
   

    //InjectHook(0x407480, &CStreamingInfo::AddToList, PATCH_JUMP);
    //InjectHook(0x4076A0, &CStreaming::IsVeryBusy, PATCH_JUMP);
    //InjectHook(0x4087E0, &CStreaming::RequestModel, PATCH_JUMP);

    DetourTransactionCommit(); 
   */
}

