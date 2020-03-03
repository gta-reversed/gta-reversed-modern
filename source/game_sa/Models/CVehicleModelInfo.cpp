/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

RwTexture* CVehicleModelInfo::ms_pRemapTexture = (RwTexture*)0xB4E47C;
RwTexture* CVehicleModelInfo::ms_pLightsTexture = (RwTexture*)0xB4E68C;
RwTexture* CVehicleModelInfo::ms_pLightsOnTexture = (RwTexture*)0xB4E690;
unsigned char* CVehicleModelInfo::ms_currentCol = (unsigned char*)0xB4E3F0;
CRGBA* CVehicleModelInfo::ms_vehicleColourTable = (CRGBA*)0xB4E480;
char* CVehicleModelInfo::ms_compsUsed = (char*)0xB4E478;
char* CVehicleModelInfo::ms_compsToUse = (char*)0x8A6458;

typedef CVehicleModelInfo::CVehicleStructure CVehicleStructure;
CPool<CVehicleStructure>*& CVehicleStructure::m_pInfoPool = *(CPool<CVehicleStructure> * *)0xB4E680;
RwObjectNameIdAssocation** CVehicleModelInfo::ms_vehicleDescs = (RwObjectNameIdAssocation * *)0x8A7740;

void CVehicleModelInfo::InjectHooks()
{
    HookInstall(0x4C95C0, &CVehicleModelInfo::SetClump_Reversed, 7);
}

CVehicleStructure* CVehicleStructure::Constructor()
{
    return plugin::CallMethodAndReturn<CVehicleStructure*, 0x4C8D60, CVehicleStructure*>(this);
}

void CVehicleModelInfo::SetClump(RpClump* clump)
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall*)(CClumpModelInfo*, RpClump*))plugin::GetVMT(this, 16))(this, clump);
#else
    SetClump_Reversed(clump);
#endif
}

void CVehicleModelInfo::SetClump_Reversed(RpClump* clump)
{
    auto pVehicleStructure = (CVehicleStructure*)CVehicleStructure::m_pInfoPool->New();
    if (pVehicleStructure)
    {
        pVehicleStructure->Constructor();
    }

    m_pVehicleStruct = pVehicleStructure;
    CClumpModelInfo::SetClump(clump);
    SetAtomicRenderCallbacks();
    SetFrameIds(ms_vehicleDescs[m_nVehicleType]);
    SetRenderPipelines();
    PreprocessHierarchy();
    ReduceMaterialsInVehicle();
    m_nCurrentPrimaryColor = 255;
    m_nCurrentSecondaryColor = 255;
    m_nCurrentTertiaryColor = 255;
    m_nCurrentQuaternaryColor = 255;
    SetCarCustomPlate();
}


void CVehicleModelInfo::ShutdownLightTexture()
{
    ((void(__cdecl*)())0x4C7470)();
}

RwTexture* CVehicleModelInfo::FindTextureCB(char const* name)
{
    return ((RwTexture * (__cdecl*)(char const*))0x4C7510)(name);
}

void CVehicleModelInfo::UseCommonVehicleTexDicationary()
{
    ((void(__cdecl*)())0x4C75A0)();
}

void CVehicleModelInfo::StopUsingCommonVehicleTexDicationary()
{
    ((void(__cdecl*)())0x4C75C0)();
}

RpAtomic* CVehicleModelInfo::MoveObjectsCB(RwObject* object, void* data)
{
    return ((RpAtomic * (__cdecl*)(RwObject*, void*))0x4C7700)(object, data);
}

RpAtomic* CVehicleModelInfo::HideDamagedAtomicCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x4C7720)(atomic, data);
}

RpAtomic* CVehicleModelInfo::HideAllComponentsAtomicCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x4C7790)(atomic, data);
}

RpMaterial* CVehicleModelInfo::HasAlphaMaterialCB(RpMaterial* material, void* data)
{
    return ((RpMaterial * (__cdecl*)(RpMaterial*, void*))0x4C77C0)(material, data);
}

RpAtomic* CVehicleModelInfo::SetAtomicRendererCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x4C77E0)(atomic, data);
}

RpAtomic* CVehicleModelInfo::SetAtomicRendererCB_RealHeli(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x4C7870)(atomic, data);
}

RpAtomic* CVehicleModelInfo::SetAtomicRendererCB_Plane(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x4C7930)(atomic, data);
}

RpAtomic* CVehicleModelInfo::SetAtomicRendererCB_Boat(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x4C79A0)(atomic, data);
}

RpAtomic* CVehicleModelInfo::SetAtomicRendererCB_Heli(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x4C7A30)(atomic, data);
}

RpAtomic* CVehicleModelInfo::SetAtomicRendererCB_Train(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x4C7AA0)(atomic, data);
}

void CVehicleModelInfo::SetAtomicRenderCallbacks()
{
    ((void(__thiscall*)(CVehicleModelInfo*))0x4C7B10)(this);
}

RwObject* CVehicleModelInfo::SetAtomicFlagCB(RwObject* object, void* data)
{
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x4C7B90)(object, data);
}

// Converted from stdcall RwObject* CVehicleModelInfo::ClearAtomicFlagCB(RwObject *object, void *data) 0x4C7BB0
RwObject* CVehicleModelInfo::ClearAtomicFlagCB(RwObject* object, void* data)
{
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x4C7BB0)(object, data);
}

// Converted from thiscall void CVehicleModelInfo::SetVehicleComponentFlags(RwFrame *component, unsigned int flags) 0x4C7C10
void CVehicleModelInfo::SetVehicleComponentFlags(RwFrame* component, unsigned int flags)
{
    ((void(__thiscall*)(CVehicleModelInfo*, RwFrame*, unsigned int))0x4C7C10)(this, component, flags);
}

// Converted from thiscall void CVehicleModelInfo::GetWheelPosn(int wheel, CVector &outVec, bool local) 0x4C7D20
void CVehicleModelInfo::GetWheelPosn(int wheel, CVector& outVec, bool local)
{
    ((void(__thiscall*)(CVehicleModelInfo*, int, CVector&, bool))0x4C7D20)(this, wheel, outVec, local);
}

// Converted from thiscall bool CVehicleModelInfo::GetOriginalCompPosition(CVector &outVec, int component) 0x4C7DD0
bool CVehicleModelInfo::GetOriginalCompPosition(CVector& outVec, int component)
{
    return ((bool(__thiscall*)(CVehicleModelInfo*, CVector&, int))0x4C7DD0)(this, outVec, component);
}

// Converted from thiscall int CVehicleModelInfo::ChooseComponent(void) 0x4C8040
int CVehicleModelInfo::ChooseComponent()
{
    return ((int(__thiscall*)(CVehicleModelInfo*))0x4C8040)(this);
}

// Converted from thiscall int CVehicleModelInfo::ChooseSecondComponent(void) 0x4C8120
int CVehicleModelInfo::ChooseSecondComponent()
{
    return ((int(__thiscall*)(CVehicleModelInfo*))0x4C8120)(this);
}

// Converted from thiscall bool CVehicleModelInfo::IsUpgradeAvailable(VehicleUpgradePosn upgrade) 0x4C8200
bool CVehicleModelInfo::IsUpgradeAvailable(VehicleUpgradePosn upgrade)
{
    return ((bool(__thiscall*)(CVehicleModelInfo*, VehicleUpgradePosn))0x4C8200)(this, upgrade);
}

RpMaterial* CVehicleModelInfo::SetEditableMaterialsCB(RpMaterial* material, void* data)
{
    return ((RpMaterial * (__cdecl*)(RpMaterial*, void*))0x4C8220)(material, data);
}

RpAtomic* CVehicleModelInfo::SetEditableMaterialsCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x4C83E0)(atomic, data);
}

// Converted from stdcall void CVehicleModelInfo::SetEditableMaterials(RpClump *clump) 0x4C8430
void CVehicleModelInfo::SetEditableMaterials(RpClump* clump)
{
    ((void(__cdecl*)(RpClump*))0x4C8430)(clump);
}

// Converted from stdcall void CVehicleModelInfo::ResetEditableMaterials(RpClump *clump) 0x4C8460
void CVehicleModelInfo::ResetEditableMaterials(RpClump* clump)
{
    ((void(__cdecl*)(RpClump*))0x4C8460)(clump);
}

// Converted from thiscall void CVehicleModelInfo::SetVehicleColour(unsigned char prim, unsigned char sec, unsigned char tert, unsigned char quat) 0x4C84B0
void CVehicleModelInfo::SetVehicleColour(unsigned char prim, unsigned char sec, unsigned char tert, unsigned char quat)
{
    ((void(__thiscall*)(CVehicleModelInfo*, unsigned char, unsigned char, unsigned char, unsigned char))0x4C84B0)(this, prim, sec, tert, quat);
}

// Converted from thiscall void CVehicleModelInfo::ChooseVehicleColour(unsigned char &prim, unsigned char &sec, unsigned char &tert, unsigned char &quat, int variationShift) 0x4C8500
void CVehicleModelInfo::ChooseVehicleColour(unsigned char& prim, unsigned char& sec, unsigned char& tert, unsigned char& quat, int variationShift)
{
    ((void(__thiscall*)(CVehicleModelInfo*, unsigned char&, unsigned char&, unsigned char&, unsigned char&, int))0x4C8500)(this, prim, sec, tert, quat, variationShift);
}

// Converted from thiscall int CVehicleModelInfo::GetNumRemaps(void) 0x4C86B0
int CVehicleModelInfo::GetNumRemaps()
{
    return ((int(__thiscall*)(CVehicleModelInfo*))0x4C86B0)(this);
}

// Converted from thiscall void CVehicleModelInfo::AddRemap(int txd) 0x4C86D0
void CVehicleModelInfo::AddRemap(int txd)
{
    ((void(__thiscall*)(CVehicleModelInfo*, int))0x4C86D0)(this, txd);
}

// Converted from stdcall void CVehicleModelInfo::AddWheelUpgrade(int wheelSetNumber, int modelId) 0x4C8700
void CVehicleModelInfo::AddWheelUpgrade(int wheelSetNumber, int modelId)
{
    ((void(__cdecl*)(int, int))0x4C8700)(wheelSetNumber, modelId);
}

int CVehicleModelInfo::GetNumWheelUpgrades(int wheelSetNumber)
{
    return ((int(__cdecl*)(int))0x4C8740)(wheelSetNumber);
}

void CVehicleModelInfo::GetWheelUpgrade(int wheelSetNumber, int wheelUpgradeNumber)
{
    ((void(__cdecl*)(int, int))0x4C8750)(wheelSetNumber, wheelUpgradeNumber);
}

void CVehicleModelInfo::DeleteVehicleColourTextures()
{
    ((void(__cdecl*)())0x4C8770)();
}

void CVehicleModelInfo::LoadEnvironmentMaps()
{
    ((void(__cdecl*)())0x4C8780)();
}

void CVehicleModelInfo::ShutdownEnvironmentMaps()
{
    ((void(__cdecl*)())0x4C87D0)();
}

RpMaterial* CVehicleModelInfo::GetMatFXEffectMaterialCB(RpMaterial* material, void* data)
{
    return ((RpMaterial * (__cdecl*)(RpMaterial*, void*))0x4C8810)(material, data);
}

RpMaterial* CVehicleModelInfo::SetEnvironmentMapCB(RpMaterial* material, void* data)
{
    return ((RpMaterial * (__cdecl*)(RpMaterial*, void*))0x4C8840)(material, data);
}

RpMaterial* CVehicleModelInfo::SetEnvMapCoeffCB(RpMaterial* material, void* data)
{
    return ((RpMaterial * (__cdecl*)(RpMaterial*, void*))0x4C88B0)(material, data);
}

RpAtomic* CVehicleModelInfo::SetRenderPipelinesCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x4C88F4)(atomic, data);
}

void CVehicleModelInfo::SetRenderPipelines()
{
    ((void(__thiscall*)(CVehicleModelInfo*))0x4C8900)(this);
}

char* CVehicleModelInfo::GetCustomCarPlateText()
{
    return ((char* (__thiscall*)(CVehicleModelInfo*))0x4C8970)(this);
}

void CVehicleModelInfo::SetCustomCarPlateText(char* text)
{
    ((void(__thiscall*)(CVehicleModelInfo*, char*))0x4C8980)(this, text);
}

int CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(int modelId)
{
    return ((int(__cdecl*)(int))0x4C89B0)(modelId);
}

void CVehicleModelInfo::ReduceMaterialsInVehicle()
{
    ((void(__thiscall*)(CVehicleModelInfo*))0x4C8BD0)(this);
}

void CVehicleModelInfo::SetupLightFlags(CVehicle* vehicle)
{
    ((void(__thiscall*)(CVehicleModelInfo*, CVehicle*))0x4C8C90)(this, vehicle);
}

RwFrame* CVehicleModelInfo::CollapseFramesCB(RwFrame* frame, void* data)
{
    return ((RwFrame * (__cdecl*)(RwFrame*, void*))0x4C8E30)(frame, data);
}

void CVehicleModelInfo::PreprocessHierarchy()
{
    ((void(__thiscall*)(CVehicleModelInfo*))0x4C8E60)(this);
}

RpAtomic* CVehicleModelInfo::SetEnvironmentMapAtomicCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x4C9410)(atomic, data);
}

RpAtomic* CVehicleModelInfo::SetEnvMapCoeffAtomicCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x4C9430)(atomic, data);
}

void CVehicleModelInfo::SetCarCustomPlate()
{
    ((void(__thiscall*)(CVehicleModelInfo*))0x4C9450)(this);
}

void CVehicleModelInfo::DisableEnvMap()
{
    ((void(__thiscall*)(CVehicleModelInfo*))0x4C97E0)(this);
}

void CVehicleModelInfo::SetEnvMapCoeff(float coeff)
{
    ((void(__thiscall*)(CVehicleModelInfo*, float))0x4C9800)(this, coeff);
}

int CVehicleModelInfo::GetNumDoors()
{
    return ((int(__thiscall*)(CVehicleModelInfo*))0x4C73C0)(this);
}