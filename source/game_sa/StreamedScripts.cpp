#include "StdInc.h"

#include "StreamedScripts.h"

void CStreamedScripts::InjectHooks() {
    RH_ScopedClass(CStreamedScripts);
    RH_ScopedCategory("Scripts");

    RH_ScopedInstall(StartNewStreamedScript, 0x470890);
}

uint32 CStreamedScripts::GetStreamedScriptWithThisStartAddress(uint8* dataPtr)
{
    uint16 result;
    for (result = 0; result < 82 && m_aScripts[result].data != dataPtr; ++result)
        ;
    return result;
}

void CStreamedScripts::Initialise() {
    plugin::CallMethod<0x470660, CStreamedScripts*>(this);
}

void CStreamedScripts::LoadStreamedScript(RwStream* stream, int32 index) {
    plugin::CallMethod<0x470840, CStreamedScripts*, RwStream*, int32>(this, stream, index);
}

void CStreamedScripts::ReInitialise() {
    plugin::CallMethod<0x4706A0, CStreamedScripts*>(this);
}

void CStreamedScripts::RemoveStreamedScriptFromMemory(int32 index) {
    plugin::CallMethod<0x4708E0, CStreamedScripts*, int32>(this, index);
}

// 0x470890
CRunningScript* CStreamedScripts::StartNewStreamedScript(int32 index)
{
    auto* pScriptInfo = &m_aScripts[index];
    uint8 *pIp = pScriptInfo->data;

    if (pIp)
    {
        CRunningScript *pNew = CTheScripts::StartNewScript(pIp);
        pNew->m_pBaseIP = pIp;
        pNew->m_bIsExternal = true;

        pScriptInfo->m_nStatus++;
        CStreaming::SetMissionDoesntRequireModel(index + RESOURCE_ID_SCM);
        return pNew;
    }

    return nullptr;
}

// 0x470750
void CStreamedScripts::ReadStreamedScriptData()
{
    plugin::CallMethod<0x470750, CStreamedScripts*>(this);
}

int32 CStreamedScripts::RegisterScript(const char* scriptName) {
    return plugin::CallMethodAndReturn<int32, 0x4706C0, CStreamedScripts*, const char*>(this, scriptName);
}
