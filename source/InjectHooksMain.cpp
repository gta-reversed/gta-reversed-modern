#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

typedef char(__cdecl *hCStreaming__FinishLoadingLargeFile)
(
    unsigned char * pFileBuffer, int modelId
);
auto OLD_CStreaming__FinishLoadingLargeFile = (hCStreaming__FinishLoadingLargeFile)0x408CB0;

char __cdecl CStreaming__FinishLoadingLargeFile(unsigned char * pFileBuffer, int modelId);

void InjectHooksMain(void)
{
   CAnimManager::InjectHooks();
   CTaskManager::InjectHooks();
   CStreaming::InjectHooks();

   /* DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CStreaming__FinishLoadingLargeFile, CStreaming__FinishLoadingLargeFile);

    DetourTransactionCommit(); */
    
}

