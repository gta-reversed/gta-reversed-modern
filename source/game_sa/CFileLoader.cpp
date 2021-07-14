/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "CCarGenerator.h"
#include "CTheCarGenerators.h"

char (&CFileLoader::ms_line)[512] = *reinterpret_cast<char (*)[512]>(0xB71848);
unsigned int& gAtomicModelId = *reinterpret_cast<unsigned int*>(0xB71840);

char (&colFileReadBuffer)[32768] = *(char (*)[32768])0xBC40D8;


void CFileLoader::InjectHooks() {
    // ReversibleHooks::Install("CFileLoader", "AddTexDictionaries", 0x5B3910, &CFileLoader::AddTexDictionaries);
    // ReversibleHooks::Install("CFileLoader", "LoadTexDictionary", 0x5B3860, &CFileLoader::LoadTexDictionary);
    // ReversibleHooks::Install("CFileLoader", "LoadAnimatedClumpObject", 0x0, &CFileLoader::LoadAnimatedClumpObject);
    ReversibleHooks::Install("CFileLoader", "LoadAtomicFile_stream", 0x5371F0, static_cast<bool(*)(RwStream*, unsigned)>(&CFileLoader::LoadAtomicFile));
    // ReversibleHooks::Install("CFileLoader", "LoadAtomicFile_filename", 0x5B39D0, static_cast<void(*)(const char*)>(&CFileLoader::LoadAtomicFile));
    // ReversibleHooks::Install("CFileLoader", "LoadLine_0", 0x536F80, static_cast<char*(*)(FILESTREAM)>(&CFileLoader::LoadLine));
    // ReversibleHooks::Install("CFileLoader", "LoadLine_1", 0x536FE0, static_cast<char*(*)(char**, int&)>(&CFileLoader::LoadLine));
    // ReversibleHooks::Install("CFileLoader", "LoadAudioZone", 0x5B4D70, &CFileLoader::LoadAudioZone);
     ReversibleHooks::Install("CFileLoader", "LoadCarGenerator_0", 0x537990, static_cast<void(*)(CFileCarGenerator*, int)>(&CFileLoader::LoadCarGenerator));
     ReversibleHooks::Install("CFileLoader", "LoadCarGenerator_1", 0x5B4740, static_cast<void(*)(const char*, int)>(&CFileLoader::LoadCarGenerator));
    // ReversibleHooks::Install("CFileLoader", "LoadCarPathNode", 0x5B4380, &CFileLoader::LoadCarPathNode);
    // ReversibleHooks::Install("CFileLoader", "StartLoadClumpFile", 0x5373F0, &CFileLoader::StartLoadClumpFile);
    // ReversibleHooks::Install("CFileLoader", "FinishLoadClumpFile", 0x537450, &CFileLoader::FinishLoadClumpFile);
    // ReversibleHooks::Install("CFileLoader", "LoadClumpFile", 0x5B3A30, static_cast<void(*)(const char*)>(&CFileLoader::LoadClumpFile));
    // ReversibleHooks::Install("CFileLoader", "LoadClumpObject", 0x5B4040, &CFileLoader::LoadClumpObject);
    // ReversibleHooks::Install("CFileLoader", "LoadCollisionFile_0", 0x538440, static_cast<bool(*)(unsigned char*, unsigned int, unsigned char)>(&CFileLoader::LoadCollisionFile));
    // ReversibleHooks::Install("CFileLoader", "LoadCollisionFile_1", 0x5B4E60, static_cast<bool(*)(const char*, unsigned char)>(&CFileLoader::LoadCollisionFile));
    // ReversibleHooks::Install("CFileLoader", "LoadCollisionFileFirstTime", 0x5B5000, &CFileLoader::LoadCollisionFileFirstTime);
    // ReversibleHooks::Install("CFileLoader", "LoadCollisionModel", 0x537580, &CFileLoader::LoadCollisionModel);
    // ReversibleHooks::Install("CFileLoader", "LoadCollisionModelVer2", 0x537EE0, &CFileLoader::LoadCollisionModelVer2);
    // ReversibleHooks::Install("CFileLoader", "LoadCollisionModelVer3", 0x537CE0, &CFileLoader::LoadCollisionModelVer3);
    // ReversibleHooks::Install("CFileLoader", "LoadCollisionModelVer4", 0x537AE0, &CFileLoader::LoadCollisionModelVer4);
    // ReversibleHooks::Install("CFileLoader", "LoadCullZone", 0x5B4B40, &CFileLoader::LoadCullZone);
    // ReversibleHooks::Install("CFileLoader", "LoadEntryExit", 0x5B8030, &CFileLoader::LoadEntryExit);
    // ReversibleHooks::Install("CFileLoader", "LoadGarage", 0x5B4530, &CFileLoader::LoadGarage);
    // ReversibleHooks::Install("CFileLoader", "LoadLevel", 0x5B9030, &CFileLoader::LoadLevel);
    ReversibleHooks::Install("CFileLoader", "LoadObject", 0x5B3C60, &CFileLoader::LoadObject);
    ReversibleHooks::Install("CFileLoader", "LoadObjectInstance_inst", 0x538090, static_cast<CEntity* (*)(CFileObjectInstance*, const char*)>(&CFileLoader::LoadObjectInstance));
    ReversibleHooks::Install("CFileLoader", "LoadObjectInstance_file", 0x538690, static_cast<CEntity* (*)(const char*)>(&CFileLoader::LoadObjectInstance));
    // ReversibleHooks::Install("CFileLoader", "LoadOcclusionVolume", 0x5B4C80, &CFileLoader::LoadOcclusionVolume);
    // ReversibleHooks::Install("CFileLoader", "LoadPathHeader", 0x5B41C0, &CFileLoader::LoadPathHeader);
    // ReversibleHooks::Install("CFileLoader", "LoadPedObject", 0x5B7420, &CFileLoader::LoadPedObject);
    // ReversibleHooks::Install("CFileLoader", "LoadPedPathNode", 0x5B41F0, &CFileLoader::LoadPedPathNode);
    // ReversibleHooks::Install("CFileLoader", "LoadPickup", 0x5B47B0, &CFileLoader::LoadPickup);
    // ReversibleHooks::Install("CFileLoader", "LoadStuntJump", 0x5B45D0, &CFileLoader::LoadStuntJump);
    // ReversibleHooks::Install("CFileLoader", "LoadTXDParent", 0x5B75E0, &CFileLoader::LoadTXDParent);
    // ReversibleHooks::Install("CFileLoader", "LoadTimeCyclesModifier", 0x5B81D0, &CFileLoader::LoadTimeCyclesModifier);
    // ReversibleHooks::Install("CFileLoader", "LoadTimeObject", 0x5B3DE0, &CFileLoader::LoadTimeObject);
    // ReversibleHooks::Install("CFileLoader", "LoadVehicleObject", 0x5B6F30, &CFileLoader::LoadVehicleObject);
    // ReversibleHooks::Install("CFileLoader", "LoadWeaponObject", 0x5B3FB0, &CFileLoader::LoadWeaponObject);
    // ReversibleHooks::Install("CFileLoader", "LoadZone", 0x5B4AB0, &CFileLoader::LoadZone);
    // ReversibleHooks::Install("CFileLoader", "LoadScene", 0x5B8700, &CFileLoader::LoadScene);
    // ReversibleHooks::Install("CFileLoader", "LoadObjectTypes", 0x5B8400, &CFileLoader::LoadObjectTypes);
    // ReversibleHooks::Install("CFileLoader", "FindRelatedModelInfoCB", 0x5B3930, &CFileLoader::FindRelatedModelInfoCB);
    ReversibleHooks::Install("CFileLoader", "SetRelatedModelInfoCB", 0x537150, &CFileLoader::SetRelatedModelInfoCB);
}

// copy textures from dictionary to baseDictionary
// 0x5B3910
void CFileLoader::AddTexDictionaries(RwTexDictionary* dictionary, RwTexDictionary* baseDictionary) {
    plugin::Call<0x5B3910, RwTexDictionary*, RwTexDictionary*>(dictionary, baseDictionary);
}

// save txd to file
// unused
// 0x5B38C0
void CFileLoader::SaveTexDictionary(RwTexDictionary* dictionary, const char* filename) {
    return plugin::Call<0x5B38C0, RwTexDictionary*, const char*>(dictionary, filename);
}

// load txd from file
// 0x5B3860
RwTexDictionary* CFileLoader::LoadTexDictionary(const char* filename) {
    return plugin::CallAndReturn<RwTexDictionary*, 0x5B3860, const char*>(filename);
}

// 0x5B40C0
int CFileLoader::LoadAnimatedClumpObject(const char* line) {
    return plugin::CallAndReturn<int, 0x5B40C0, const char*>(line);
}

// 0x5371F0
bool CFileLoader::LoadAtomicFile(RwStream* stream, unsigned int modelId) {
    auto pAtomicModelInfo = CModelInfo::ms_modelInfoPtrs[modelId]->AsAtomicModelInfoPtr();
    bool bUseCommonVehicleTexDictionary = false;
    if (pAtomicModelInfo && pAtomicModelInfo->bUseCommonVehicleDictionary) {
        bUseCommonVehicleTexDictionary = true;
        CVehicleModelInfo::UseCommonVehicleTexDicationary();
    }

    if (RwStreamFindChunk(stream, rwID_CLUMP, nullptr, nullptr)) {
        RpClump* pReadClump = RpClumpStreamRead(stream);
        if (!pReadClump) {
            if (bUseCommonVehicleTexDictionary) {
                CVehicleModelInfo::StopUsingCommonVehicleTexDicationary();
            }
            return false;
        }
        gAtomicModelId = modelId;
        RpClumpForAllAtomics(pReadClump, (RpAtomicCallBack)SetRelatedModelInfoCB, pReadClump);
        RpClumpDestroy(pReadClump);
    }

    if (!pAtomicModelInfo->m_pRwObject)
        return false;

    if (bUseCommonVehicleTexDictionary)
        CVehicleModelInfo::StopUsingCommonVehicleTexDicationary();

    return true;
}

// 0x5B39D0
void CFileLoader::LoadAtomicFile(const char* filename) {
    plugin::Call<0x5B39D0, const char*>(filename);
}

// unused
// 0x537060
RpClump* CFileLoader::LoadAtomicFile2Return(const char* filename) {
    return plugin::CallAndReturn<RpClump*, 0x537060, const char*>(filename);
}

// 0x536F80
char* CFileLoader::LoadLine(FILESTREAM file) {
    return plugin::CallAndReturn<char*, 0x536F80, FILESTREAM>(file);
}

// 0x536FE0
char* CFileLoader::LoadLine(char** outLine, int& outSize) {
    return plugin::CallAndReturn<char*, 0x536FE0, char**, int&>(outLine, outSize);;
}

// IPL -> AUZO
// 0x5B4D70
void CFileLoader::LoadAudioZone(const char* line) {
    plugin::Call<0x5B4D70, const char*>(line);
}

// unused?
// 0x0
void CFileLoader::LoadBoundingBox(unsigned char* data, CBoundingBox& outBoundBox) {

}

// 0x537990
void CFileLoader::LoadCarGenerator(CFileCarGenerator* carGen, int iplId) {
    auto index = CTheCarGenerators::CreateCarGenerator(
        carGen->m_vecPosn,
        RWRAD2DEG(carGen->m_fAngle),
        carGen->m_nModelId,
        carGen->m_nPrimaryColor,
        carGen->m_nSecondaryColor,
        carGen->m_bForceSpawn,
        carGen->m_nAlarmChance,
        carGen->m_nDoorLockChance,
        carGen->m_nMinDelay,
        carGen->m_nMaxDelay,
        iplId,
        carGen->m_bIgnorePopulationLimit
    );
    if (index >= 0)
        CTheCarGenerators::Get(index)->SwitchOn();
}

// IPL -> CARS
// 0x5B4740
void CFileLoader::LoadCarGenerator(const char* line, int iplId) {
    CFileCarGenerator carGen;
    auto iNumRead = sscanf(
        line,
        "%f %f %f %f %d %d %d %d %d %d %d %d",
        &carGen.m_vecPosn.x,
        &carGen.m_vecPosn.y,
        &carGen.m_vecPosn.z,
        &carGen.m_fAngle,
        &carGen.m_nModelId,
        &carGen.m_nPrimaryColor,
        &carGen.m_nSecondaryColor,
        &carGen.m_nFlags,
        &carGen.m_nAlarmChance,
        &carGen.m_nDoorLockChance,
        &carGen.m_nMinDelay,
        &carGen.m_nMaxDelay
    );
    if (iNumRead == 12)
        LoadCarGenerator(&carGen, iplId);
}

// 0x5B4380
void CFileLoader::LoadCarPathNode(const char* line, int objModelIndex, int pathEntryIndex, bool a4) {
    plugin::Call<0x5B4380, const char*, int, int, bool>(line, objModelIndex, pathEntryIndex, a4);
}

// 0x5373F0
bool CFileLoader::StartLoadClumpFile(RwStream* stream, unsigned int modelIndex) {
    return plugin::CallAndReturn<bool, 0x5373F0, RwStream*, unsigned int>(stream, modelIndex);
}

// 0x537450
bool CFileLoader::FinishLoadClumpFile(RwStream* stream, unsigned int modelIndex) {
    return plugin::CallAndReturn<bool, 0x537450, RwStream*, unsigned int>(stream, modelIndex);
}

// 0x5372D0
bool CFileLoader::LoadClumpFile(RwStream* stream, unsigned int modelIndex) {
    return plugin::CallAndReturn<bool, 0x5372D0, RwStream*, unsigned int>(stream, modelIndex);
}

// 0x5B3A30
void CFileLoader::LoadClumpFile(const char* filename) {
    plugin::Call<0x5B3A30, const char*>(filename);
}

// 0x5B4040
int CFileLoader::LoadClumpObject(const char* line) {
    return plugin::CallAndReturn<int, 0x5B4040, const char*>(line);
}

// 0x538440
bool CFileLoader::LoadCollisionFile(unsigned char* data, unsigned int dataSize, unsigned char colId) {
    return plugin::CallAndReturn<bool, 0x538440, unsigned char*, unsigned int, unsigned char>(data, dataSize, colId);
}

// 0x5B4E60
bool CFileLoader::LoadCollisionFile(const char* filename, unsigned char colId) {
    return plugin::CallAndReturn<bool, 0x5B4E60, const char*, unsigned char>(filename, colId);
}

// 0x5B5000
bool CFileLoader::LoadCollisionFileFirstTime(unsigned char* data, unsigned int dataSize, unsigned char colId) {
    return plugin::CallAndReturn<bool, 0x5B5000, unsigned char*, unsigned int, unsigned char>(data, dataSize, colId);
}

// 0x537580
void CFileLoader::LoadCollisionModel(unsigned char* data, CColModel& outColModel) {
    plugin::Call<0x537580, unsigned char*, CColModel&>(data, outColModel);
}

// 0x537EE0
void CFileLoader::LoadCollisionModelVer2(unsigned char* data, unsigned int dataSize, CColModel& outColModel, const char* modelName) {
    plugin::Call<0x537EE0, unsigned char*, unsigned int, CColModel&, const char*>(data, dataSize, outColModel, modelName);
}

// 0x537CE0
void CFileLoader::LoadCollisionModelVer3(unsigned char* data, unsigned int dataSize, CColModel& outColModel, const char* modelName) {
    plugin::Call<0x537CE0, unsigned char*, unsigned int, CColModel&, const char*>(data, dataSize, outColModel, modelName);
}

// 0x537AE0
void CFileLoader::LoadCollisionModelVer4(unsigned char* data, unsigned int dataSize, CColModel& outColModel, const char* modelName) {
    plugin::Call<0x537AE0, unsigned char*, unsigned int, CColModel&, const char*>(data, dataSize, outColModel, modelName);
}

// 0x5B3C60
int CFileLoader::LoadObject(const char* line) {
    int   modelId;
    char  modelName[24];
    char  texName[24];
    float fDrawDist;
    uint  nFlags;

    auto iNumRead = sscanf(line, "%d %s %s %f %d", &modelId, modelName, texName, &fDrawDist, &nFlags);
    if (iNumRead != 5 || fDrawDist < 4.0f) {
        int objType;
        float fDrawDist2_unused, fDrawDist3_unused;
        iNumRead = sscanf((char*)line, "%d %s %s %d", &modelId, modelName, texName, &objType);
        if (iNumRead != 4)
            return -1;

        switch (objType) {
        case 1:
            sscanf(line, "%d %s %s %d %f %d", &modelId, modelName, texName, &objType, &fDrawDist, &nFlags);
            break;
        case 2:
            sscanf(line, "%d %s %s %d %f %f %d", &modelId, modelName, texName, &objType, &fDrawDist, &fDrawDist2_unused, &nFlags);
            break;
        case 3:
            sscanf(line, "%d %s %s %d %f %f %f %d", &modelId, modelName, texName, &objType, &fDrawDist, &fDrawDist2_unused, &fDrawDist3_unused, &nFlags);
            break;
        }
    }

    sItemDefinitionFlags flags(nFlags);
    CAtomicModelInfo* pModelInfo;
    if (flags.bIsDamageable)
        pModelInfo = CModelInfo::AddDamageAtomicModel(modelId);
    else
        pModelInfo = CModelInfo::AddAtomicModel(modelId);

    pModelInfo->m_fDrawDistance = fDrawDist;
    pModelInfo->SetModelName(modelName);
    pModelInfo->SetTexDictionary(texName);
    SetAtomicModelInfoFlags(pModelInfo, nFlags);
    return modelId;
}

// 0x5B7670
void CFileLoader::Load2dEffect(const char* line) {
    plugin::Call<0x5B7670, const char*>(line);
}

// 0x538090
CEntity* CFileLoader::LoadObjectInstance(CFileObjectInstance* objInstance, const char* modelName) {
    auto* pInfo = CModelInfo::GetModelInfo(objInstance->m_nModelId);
    if (!pInfo)
        return nullptr;

    CEntity* pNewEntity = nullptr;
    if (pInfo->m_nObjectInfoIndex == -1)
    {
        if (pInfo->GetModelType() == ModelInfoType::MODEL_INFO_CLUMP && pInfo->bHasAnimBlend)
            pNewEntity = new CAnimatedBuilding();
        else
            pNewEntity = new CBuilding();

        pNewEntity->SetModelIndexNoCreate(objInstance->m_nModelId);
        if (pInfo->bDontCastShadowsOn)
            pNewEntity->m_bDontCastShadowsOn = true;

        if (pInfo->m_fDrawDistance < 2.0F)
            pNewEntity->m_bIsVisible = false;
    }
    else
    {
        pNewEntity = new CDummyObject();
        pNewEntity->SetModelIndexNoCreate(objInstance->m_nModelId);
        if (IsGlassModel(pNewEntity) && !CModelInfo::GetModelInfo(pNewEntity->m_nModelIndex)->IsGlassType2())
            pNewEntity->m_bIsVisible = false;
    }

    if (fabs(objInstance->m_qRotation.imag.x) > 0.05F
    || fabs(objInstance->m_qRotation.imag.y) > 0.05F
    || (objInstance->m_bDontStream && objInstance->m_qRotation.imag.x != 0.0f&& objInstance->m_qRotation.imag.y != 0.0f))
    {
        objInstance->m_qRotation.imag = -objInstance->m_qRotation.imag;
        pNewEntity->AllocateStaticMatrix();

        auto tempQuat = objInstance->m_qRotation;
        pNewEntity->GetMatrix().SetRotate(tempQuat);
    }
    else
    {
        const auto fMult = objInstance->m_qRotation.imag.z < 0.0f ? 2.0f : -2.0f;
        const auto fHeading = acos(objInstance->m_qRotation.real) * fMult;
        pNewEntity->SetHeading(fHeading);
    }

    pNewEntity->SetPosn(objInstance->m_vecPosition);

    if (objInstance->m_bUnderwater)
        pNewEntity->m_bUnderwater = true;

    if (objInstance->m_bTunnel)
        pNewEntity->m_bTunnel = true;

    if (objInstance->m_bTunnelTransition)
        pNewEntity->m_bTunnelTransition = true;

    pNewEntity->m_nAreaCode = objInstance->m_nAreaCode;
    pNewEntity->m_nLodIndex = objInstance->m_nLodInstanceIndex;

    if (objInstance->m_nModelId == ModelIndices::MI_TRAINCROSSING)
    {
        pNewEntity->AllocateStaticMatrix();
        CObject::SetMatrixForTrainCrossing(&pNewEntity->GetMatrix(), PI * 0.43f);
    }

    auto* pColModel = pInfo->GetColModel();
    if (pColModel)
    {
        if (pColModel->m_boundSphere.m_bFlag0x01)
        {
            if (pColModel->m_boundSphere.m_nColSlot)
            {
                CRect rect;
                pNewEntity->GetBoundRect(&rect);
                auto* pColDef = CColStore::ms_pColPool->GetAt(pColModel->m_boundSphere.m_nColSlot);
                pColDef->m_Area.Restrict(rect);
            }
        }
        else
        {
            pNewEntity->m_bUsesCollision = false;
        }

        if (pColModel->GetBoundingBox().m_vecMin.z + pNewEntity->GetPosition().z < 0.0f)
            pNewEntity->m_bUnderwater = true;
    }

    return pNewEntity;
}

// 0x538090
CEntity* CFileLoader::LoadObjectInstance(const char* line) {
    char modelName[24];
    CFileObjectInstance instance;

    sscanf(
        line,
        "%d %s %d %f %f %f %f %f %f %f %d",
        &instance.m_nModelId,
        modelName,
        &instance.m_nInstanceType,
        &instance.m_vecPosition.x,
        &instance.m_vecPosition.y,
        &instance.m_vecPosition.z,
        &instance.m_qRotation.imag.x,
        &instance.m_qRotation.imag.y,
        &instance.m_qRotation.imag.z,
        &instance.m_qRotation.real,
        &instance.m_nLodInstanceIndex
    );
    return LoadObjectInstance(&instance, modelName);
}

// 0x5B4B40
void CFileLoader::LoadCullZone(const char* line) {
    plugin::Call<0x5B4B40, const char*>(line);
}

// IPL -> ENEX
// 0x5B8030
void CFileLoader::LoadEntryExit(const char* line) {
    plugin::Call<0x5B8030, const char*>(line);
}

// IPL -> GRGE
// 0x5B4530
void CFileLoader::LoadGarage(const char* line) {
    return plugin::Call<0x5B4530, const char*>(line);
}

// 0x5B9030
void CFileLoader::LoadLevel(const char* filename) {
    return plugin::Call<0x5B9030, const char*>(filename);
}

// IPL -> OCCL
// 0x5B4C80
void CFileLoader::LoadOcclusionVolume(const char* line, const char* filename) {
    plugin::Call<0x5B4C80, const char*, const char*>(line, filename);
}

// 0x5B41C0
int CFileLoader::LoadPathHeader(const char* line, int& outPathType) {
    return plugin::CallAndReturn<int, 0x5B41C0, const char*, int&>(line, outPathType);
}

// PEDS
// 0x5B7420
int CFileLoader::LoadPedObject(const char* line) {
    return plugin::CallAndReturn<int, 0x5B7420, const char*>(line);
}

// useless
// 0x5B41F0
void CFileLoader::LoadPedPathNode(const char* line, int objModelIndex, int pathEntryIndex) {
    plugin::Call<0x5B41F0, const char*, int, int>(line, objModelIndex, pathEntryIndex);
}

// 0x5B47B0
void CFileLoader::LoadPickup(const char* line) {
    plugin::Call<0x5B47B0, const char*>(line);
}

// 0x5B45D0
void CFileLoader::LoadStuntJump(const char* line) {
    plugin::Call<0x5B45D0, const char*>(line);
}

// 0x5B75E0
int CFileLoader::LoadTXDParent(const char* line) {
    return plugin::CallAndReturn<int, 0x5B75E0, const char*>(line);
}

// IPL -> TCYC
// 0x5B81D0
void CFileLoader::LoadTimeCyclesModifier(const char* line) {
    return plugin::Call<0x5B81D0, const char*>(line);
}

// 0x5B3DE0
int CFileLoader::LoadTimeObject(const char* line) {
    return plugin::CallAndReturn<int, 0x5B3DE0, const char*>(line);
}

// 0x5B6F30
int CFileLoader::LoadVehicleObject(const char* line) {
    return plugin::CallAndReturn<int, 0x5B6F30, const char*>(line);
}

// 0x5B3FB0
int CFileLoader::LoadWeaponObject(const char* line) {
    return plugin::CallAndReturn<int, 0x5B3FB0, const char*>(line);
}

// 0x5B4AB0
void CFileLoader::LoadZone(const char* line) {
    plugin::Call<0x5B4AB0, const char*>(line);
}

// 0x5B51E0
void LinkLods(int a1) {
    plugin::Call<0x5B51E0, int>(a1);
}

// 0x5B8700
void CFileLoader::LoadScene(const char* filename) {
    plugin::Call<0x5B8700, const char*>(filename);
}

// 0x5B8400
void CFileLoader::LoadObjectTypes(const char* filename) {
    plugin::Call<0x5B8400, const char*>(filename);
}

// 0x5B3AC0
void CFileLoader::ReloadObjectTypes(const char* arg1) {
    // NOP
}

// Izzotop: Untested and may be wrong, see at your own risk
// unused
// 0x5B6E10
void CFileLoader::ReloadPaths(const char* filename) {
    int  objModelIndex;
    int  id;
    char unused[4];

    bool pathAllocated = false;
    int pathEntryIndex = -1;
    FILESTREAM file = CFileMgr::OpenFile(filename, "r");
    for (char* line = LoadLine(file); line; line = LoadLine(file)) {
        if (*line == '#' || !*line)
            continue;

        if (pathAllocated) {
            if (make_fourcc3(line, "end")) {
                pathAllocated = false;
            } else if (pathEntryIndex == -1) {
                sscanf(line, "%d %d %s", &id, &objModelIndex, unused);
                pathEntryIndex = 0;
            } else {
                if (id) {
                    if (id == 1) {
                        LoadCarPathNode(line, objModelIndex, pathEntryIndex, false);
                    } else if (id == 2) {
                        LoadCarPathNode(line, objModelIndex, pathEntryIndex, true);
                    }
                } else {
                    LoadPedPathNode(line, objModelIndex, pathEntryIndex);
                }

                if (++pathEntryIndex == 12)
                    pathEntryIndex = -1;
            }
        } else if (make_fourcc4(line, "path")) {
            pathAllocated = true;
            CPathFind::AllocatePathFindInfoMem();
        }
    }

    CFileMgr::CloseFile(file);
}

/**
 * @param atomic callback atomic
 * @param data clump object (RpClump*)
 * @return callback atomic
 * @addr 0x537150
 */
RpAtomic* CFileLoader::SetRelatedModelInfoCB(RpAtomic* atomic, void* data) {
    char name[24] = {0};
    bool bDamage = false;

    auto pAtomicModelInfo = CModelInfo::GetModelInfo(gAtomicModelId)->AsAtomicModelInfoPtr();
    const char* frameNodeName = GetFrameNodeName(RpAtomicGetFrame(atomic));

    GetNameAndDamage(frameNodeName, name, bDamage);
    CVisibilityPlugins::SetAtomicRenderCallback(atomic, nullptr);
    if (bDamage) {
        pAtomicModelInfo->AsDamageAtomicModelInfoPtr()->SetDamagedAtomic(atomic);
    } else {
        pAtomicModelInfo->SetAtomic(atomic);
    }
    RpClumpRemoveAtomic(static_cast<RpClump*>(data), atomic);
    RwFrame* newFrame = RwFrameCreate();
    RpAtomicSetFrame(atomic, newFrame);
    CVisibilityPlugins::SetAtomicId(atomic, gAtomicModelId);
    return atomic;
}
