#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

typedef char(__cdecl *hCStreaming__ConvertBufferToObject)
(
    unsigned char * pBuffer, int modelId
);
auto OLD_CStreaming__ConvertBufferToObject = (hCStreaming__ConvertBufferToObject)0x40C6B0;

char __cdecl CStreaming__ConvertBufferToObject(unsigned char * pBuffer, int modelId);


void InjectHooksMain(void)
{
   CAnimManager::InjectHooks();
   CTaskManager::InjectHooks();
   CStreaming::InjectHooks();

    /*DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CStreaming__ConvertBufferToObject, CStreaming__ConvertBufferToObject);

    DetourTransactionCommit(); */
    
}
