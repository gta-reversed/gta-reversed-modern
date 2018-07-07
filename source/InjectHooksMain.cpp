#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")


typedef char(__cdecl*  hCStreaming__ProcessLoadingChannel)
(
    int channelIndex
);

auto OLD_CStreaming__ProcessLoadingChannel = (hCStreaming__ProcessLoadingChannel)0x40E170;
char __cdecl CStreaming__ProcessLoadingChannel(int channelIndex);

void InjectHooksMain(void)
{
    InjectHook(0x15674C0, &CStreamingInfo::AddToList, PATCH_JUMP);
    InjectHook(0x40A45E, &CStreaming::LoadAllRequestedModels, PATCH_JUMP);
    InjectHook(0x4087E0, &CStreaming::RequestModel, PATCH_JUMP);
    InjectHook(0x40E170, &CStreaming::ProcessLoadingChannel, PATCH_JUMP);
    InjectHook(0x40E460, &CStreaming::FlushChannels, PATCH_JUMP);
    /*DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CStreaming__ProcessLoadingChannel, CStreaming__ProcessLoadingChannel);
  
    DetourTransactionCommit(); */
   
}
