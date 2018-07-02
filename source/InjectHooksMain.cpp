#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

/*
typedef void (__cdecl*  hCStreaming__RequestModel)
(
    //signed int dwModelId, char flags
    int dwModelId, char streamingFlags
);

hCStreaming__RequestModel OLD_CStreaming__RequestModel = (hCStreaming__RequestModel)0x4087E0;

void __cdecl CStreaming__RequestModel(int dwModelId, char streamingFlags);*/

void InjectHooksMain(void)
{
    InjectHook(0x15674C0, &CStreamingInfo::AddToList, PATCH_JUMP);
    InjectHook(0x4087E0, &CStreaming::RequestModel, PATCH_JUMP);

    /*
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CStreaming__RequestModel, CStreaming__RequestModel);
   

    //InjectHook(0x407480, &CStreamingInfo::AddToList, PATCH_JUMP);
    //InjectHook(0x4076A0, &CStreaming::IsVeryBusy, PATCH_JUMP);
    //InjectHook(0x4087E0, &CStreaming::RequestModel, PATCH_JUMP);

    DetourTransactionCommit(); */
   
}
