#include "StdInc.h"

CPool<CPed, CCopPed>*& CPools::ms_pPedPool = *(CPool<CPed, CCopPed>**)0xB74490;
CPool<CVehicle, CHeli>*& CPools::ms_pVehiclePool = *(CPool<CVehicle, CHeli>**)0xB74494;
CPool<CBuilding>*& CPools::ms_pBuildingPool = *(CPool<CBuilding>**)0xB74498;
CPool<CObject, CCutsceneObject>*& CPools::ms_pObjectPool = *(CPool<CObject, CCutsceneObject>**)0xB7449C;
CPool<CDummy>*& CPools::ms_pDummyPool = *(CPool<CDummy>**)0xB744A0;
CPool<CColModel>*& CPools::ms_pColModelPool = *(CPool<CColModel>**)0xB744A4;
CPool<CTask, CTaskSimpleSlideToCoord>*& CPools::ms_pTaskPool = *(CPool<CTask, CTaskSimpleSlideToCoord>**)0xB744A8;
CPool<CPedIntelligence>*& CPools::ms_pPedIntelligencePool = *(CPool<CPedIntelligence>**)0xB744C0;
CPool<CPtrNodeSingleLink>*& CPools::ms_pPtrNodeSingleLinkPool = *(CPool<CPtrNodeSingleLink>**)0xB74484;
CPool<CPtrNodeDoubleLink>*& CPools::ms_pPtrNodeDoubleLinkPool = *(CPool<CPtrNodeDoubleLink>**)0xB74488;
CPool<CEntryInfoNode>*& CPools::ms_pEntryInfoNodePool = *(CPool<CEntryInfoNode>**)0xB7448C;
CPool<CPointRoute>*& CPools::ms_pPointRoutePool = *(CPool<CPointRoute>**)0xB744B0;

void CPools::InjectHooks()
{
    ReversibleHooks::Install("CPools", "LoadObjectPool", 0x5D4A40, &CPools::LoadObjectPool);
    ReversibleHooks::Install("CPools", "MakeSureSlotInObjectPoolIsEmpty", 0x550080, &CPools::MakeSureSlotInObjectPoolIsEmpty);
}

int CPools::CheckBuildingAtomics() {
    return plugin::CallAndReturn<int, 0x550170>();
}

// Converted from cdecl void CPools::CheckPoolsEmpty(void) 0x551950
void CPools::CheckPoolsEmpty() {
    plugin::Call<0x551950>();
}

// Converted from cdecl CObject* CPools::GetObject(int handle) 0x550050
CObject* CPools::GetObject(int handle) {
    return plugin::CallAndReturn<CObject*, 0x550050, int>(handle);
}

// Converted from cdecl int CPools::GetObjectRef(CObject *object) 0x550020
int CPools::GetObjectRef(CObject* object) {
    return plugin::CallAndReturn<int, 0x550020, CObject*>(object);
}

// Converted from cdecl CPed* CPools::GetPed(int handle) 0x54FF90
CPed* CPools::GetPed(int handle) {
    return plugin::CallAndReturn<CPed*, 0x54FF90, int>(handle);
}

// Converted from cdecl int CPools::GetPedRef(CPed *ped) 0x54FF60
int CPools::GetPedRef(CPed* ped) {
    return plugin::CallAndReturn<int, 0x54FF60, CPed*>(ped);
}

// Converted from cdecl CVehicle* CPools::GetVehicle(int) 0x54FFF0
CVehicle* CPools::GetVehicle(int handle) {
    return plugin::CallAndReturn<CVehicle*, 0x54FFF0, int>(handle);
}

// Converted from cdecl int CPools::GetVehicleRef(CVehicle *vehicle) 0x54FFC0
int CPools::GetVehicleRef(CVehicle* vehicle) {
    return plugin::CallAndReturn<int, 0x54FFC0, CVehicle*>(vehicle);
}

// Converted from cdecl void CPools::Initialise(void) 0x550F10
void CPools::Initialise() {
    plugin::Call<0x550F10>();
}

// Converted from cdecl bool CPools::Load(void) 0x5D0890
bool CPools::Load() {
    return plugin::CallAndReturn<bool, 0x5D0890>();
}

// Converted from cdecl bool CPools::LoadObjectPool(void) 0x5D4A40
bool CPools::LoadObjectPool() {
    int32_t iNumObjects = 0;
    CGenericGameStorage::LoadDataFromWorkBuffer(&iNumObjects, 4);
    for (int32_t i = 0; i < iNumObjects; ++i)
    {
        int32_t iPoolRef = 0, iModelId = 0;
        CGenericGameStorage::LoadDataFromWorkBuffer(&iPoolRef, 4);
        CGenericGameStorage::LoadDataFromWorkBuffer(&iModelId, 4);

        auto* pObjInPool = CPools::ms_pObjectPool->GetAtRefNoChecks(iPoolRef);
        if (pObjInPool)
            CPopulation::ConvertToDummyObject(pObjInPool);

        auto* pNewObj = new(iPoolRef) CObject(iModelId, false);
        pNewObj->Load();
        CWorld::Add(pNewObj);
    }

    return true;
}

// Converted from cdecl bool CPools::LoadPedPool(void) 0x5D2D70
bool CPools::LoadPedPool() {
    return plugin::CallAndReturn<bool, 0x5D2D70>();
}

// Converted from cdecl bool CPools::LoadVehiclePool(void) 0x5D2A20
bool CPools::LoadVehiclePool() {
    return plugin::CallAndReturn<bool, 0x5D2A20>();
}

// Converted from cdecl void CPools::MakeSureSlotInObjectPoolIsEmpty(int slot) 0x550080
void CPools::MakeSureSlotInObjectPoolIsEmpty(int slot) {
    if (CPools::ms_pObjectPool->IsFreeSlotAtIndex(slot))
        return;

    auto* pExistingObj = CPools::ms_pObjectPool->GetAt(slot);
    if (pExistingObj->IsTemporary())
    {
        CWorld::Remove(pExistingObj);
        delete pExistingObj;
    }
    else if (CProjectileInfo::RemoveIfThisIsAProjectile(pExistingObj))
    {
        auto pNewObj = new CObject(pExistingObj->m_nModelIndex, false);
        CWorld::Remove(pExistingObj);
        CPools::ms_pObjectPool->CopyItem(pNewObj, pExistingObj);
        CWorld::Add(pNewObj);

        pExistingObj->m_pRwObject = nullptr;
        delete pExistingObj;

        pNewObj->m_pReferences = nullptr;
    }
}

// Converted from cdecl bool CPools::Save(void) 0x5D0880
bool CPools::Save() {
    return plugin::CallAndReturn<bool, 0x5D0880>();
}

// Converted from cdecl bool CPools::SaveObjectPool(void) 0x5D4940
bool CPools::SaveObjectPool() {
    return plugin::CallAndReturn<bool, 0x5D4940>();
}

// Converted from cdecl bool CPools::SavePedPool(void) 0x5D4B40
bool CPools::SavePedPool() {
    return plugin::CallAndReturn<bool, 0x5D4B40>();
}

// Converted from cdecl bool CPools::SaveVehiclePool(void) 0x5D4800
bool CPools::SaveVehiclePool() {
    return plugin::CallAndReturn<bool, 0x5D4800>();
}

// Converted from cdecl void CPools::ShutDown(void) 0x5519F0
void CPools::ShutDown() {
    plugin::Call<0x5519F0>();
}
