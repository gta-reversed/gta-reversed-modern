/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

char(&CFileLoader::ms_line)[512] = *reinterpret_cast<char(*)[512]>(0xB71848);
unsigned int& gAtomicModelId = *reinterpret_cast<unsigned int*>(0xB71840);

void CFileLoader::InjectHooks()
{
    HookInstall(0x5371F0, (bool(*)(RwStream*, unsigned int))&CFileLoader::LoadAtomicFile);
    HookInstall(0x537150, &CFileLoader::SetRelatedModelInfoCB);
}

bool CFileLoader::LoadAtomicFile(RwStream *stream, unsigned int modelId) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturnDynGlobal<bool, RwStream *, unsigned int>(0x5371F0, stream, modelId);
#else
    auto pAtomicModelInfo = CModelInfo::ms_modelInfoPtrs[modelId]->AsAtomicModelInfoPtr();
    bool bUseCommonVehicleTexDictionary = false; 
    if (pAtomicModelInfo && pAtomicModelInfo->bUseCommonVehicleDictionary)
    {
        bUseCommonVehicleTexDictionary = true;
        CVehicleModelInfo::UseCommonVehicleTexDicationary();
    }

    if (RwStreamFindChunk(stream, rwID_CLUMP, nullptr, nullptr))
    {
        RpClump* pReadClump = RpClumpStreamRead(stream);
        if (!pReadClump)
        {
            if (bUseCommonVehicleTexDictionary)
            {
                CVehicleModelInfo::StopUsingCommonVehicleTexDicationary();
            }
            return false;
        }
        gAtomicModelId = modelId;
        RpClumpForAllAtomics(pReadClump, (RpAtomicCallBack)CFileLoader::SetRelatedModelInfoCB, pReadClump);
        RpClumpDestroy(pReadClump);
    }

    if (!pAtomicModelInfo->m_pRwObject)
    {
        return false;
    }

    if (bUseCommonVehicleTexDictionary)
    {
        CVehicleModelInfo::StopUsingCommonVehicleTexDicationary();
    }
    return true;
#endif
}

void CFileLoader::LoadAtomicFile(char const *filename) {
    plugin::CallDynGlobal<char const *>(0x5B39D0, filename);
}

RpClump *CFileLoader::LoadAtomicFile2Return(char const *filename) {
    return plugin::CallAndReturnDynGlobal<RpClump *, char const *>(0x537060, filename);
}

void CFileLoader::LoadCarPathNode(char const *line, int objModelIndex, int pathEntryIndex, bool a4) {
    plugin::CallDynGlobal<char const *, int, int, bool>(0x5B4380, line, objModelIndex, pathEntryIndex, a4);
}

bool CFileLoader::LoadClumpFile(RwStream *stream, unsigned int modelIndex) {
    return plugin::CallAndReturnDynGlobal<bool, RwStream *, unsigned int>(0x5372D0, stream, modelIndex);
}

void CFileLoader::LoadClumpFile(char const *filename) {
    plugin::CallDynGlobal<char const *>(0x5B3A30, filename);
}

int CFileLoader::LoadClumpObject(char const *line) {
    return plugin::CallAndReturnDynGlobal<int, char const *>(0x5B4040, line);
}

bool CFileLoader::LoadCollisionFile(unsigned char *data, unsigned int dataSize, unsigned char colId) {
    return plugin::CallAndReturnDynGlobal<bool, unsigned char *, unsigned int, unsigned char>(0x538440, data, dataSize, colId);
}

bool CFileLoader::FinishLoadClumpFile(RwStream *stream, unsigned int modelIndex) {
    return plugin::CallAndReturnDynGlobal<bool, RwStream *, unsigned int>(0x537450, stream, modelIndex);
}

void GetNameAndDamage(char const* nodeName, char* outName, bool& outDamage) {
    plugin::CallDynGlobal<char const*, char*, bool&>(0x5370A0, nodeName, outName, outDamage);
}


RpAtomic* CFileLoader::SetRelatedModelInfoCB(RpAtomic* atomic, RpClump* clump)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<RpAtomic*, 0x537150, RpAtomic*, RpClump*>(atomic, clump);
#else
    char name[24];
    auto pAtomicModelInfo = CModelInfo::ms_modelInfoPtrs[gAtomicModelId]->AsAtomicModelInfoPtr();
    char* frameNodeName = GetFrameNodeName(RpAtomicGetFrame(atomic));

    bool bDamage = false;
    GetNameAndDamage(frameNodeName, (char*)&name, bDamage);
    CVisibilityPlugins::SetAtomicRenderCallback(atomic, nullptr);
    if (bDamage)
    {
        auto pDamagableModelInfo = pAtomicModelInfo->AsDamageAtomicModelInfoPtr();
        pDamagableModelInfo->SetDamagedAtomic(atomic);
    }
    else
    {
        pAtomicModelInfo->SetAtomic(atomic);
    }
    RpClumpRemoveAtomic(clump, atomic);
    RwFrame* newFrame = RwFrameCreate();
    RpAtomicSetFrame(atomic, newFrame);
    CVisibilityPlugins::SetAtomicId(atomic, gAtomicModelId);
    return atomic;
#endif
}

char* CFileLoader::LoadLine(FILESTREAM file) {
    return plugin::CallAndReturnDynGlobal<char*, FILESTREAM>(0x536F80, file);
}
