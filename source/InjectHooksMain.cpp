#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")
    
typedef void(__cdecl*  hCStreaming__RequestModelStream)
(
    DWORD channelIndex
);

auto OLD_CStreaming__RequestModelStream = (hCStreaming__RequestModelStream)0x40CBA0;
//void __cdecl CStreaming__RequestModelStream(int32_t channelIndex);

void __cdecl CStreaming__RequestModelStream(DWORD channelIndex);

void InjectHooksMain(void)
{
    InjectHook(0x15674C0, &CStreamingInfo::AddToList, PATCH_JUMP);
    InjectHook(0x40A45E, &CStreaming::LoadAllRequestedModels, PATCH_JUMP);
    InjectHook(0x4087E0, &CStreaming::RequestModel, PATCH_JUMP);
    InjectHook(0x40E170, &CStreaming::ProcessLoadingChannel, PATCH_JUMP);
    InjectHook(0x40E460, &CStreaming::FlushChannels, PATCH_JUMP);
    InjectHook(0x40CBA0, &CStreaming::RequestModelStream, PATCH_JUMP);
    InjectHook(0x40E3A0, &CStreaming::LoadRequestedModels, PATCH_JUMP);

    //////////////
    // NOT TESTED
    //////////////
    InjectHook(0x40E4E0, &CStreaming::FlushRequestList, PATCH_JUMP);
    
    /*DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CStreaming__RequestModelStream, CStreaming__RequestModelStream);
  
    //DetourAttach(&(PVOID&)_CdStreamRead, CdStreamReadHook);
    

    DetourTransactionCommit(); */
   
}



