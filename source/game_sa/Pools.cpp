#include "StdInc.h"

#include "Pools.h"

// #include "PointRoute.h"


void CPools::InjectHooks()
{
    Install("CPools", "LoadObjectPool", 0x5D4A40, &CPools::LoadObjectPool);
    Install("CPools", "MakeSureSlotInObjectPoolIsEmpty", 0x550080, &CPools::MakeSureSlotInObjectPoolIsEmpty);
}

int32 CPools::CheckBuildingAtomics() {
    return plugin::CallAndReturn<int32, 0x550170>();
}

// 0x551950
void CPools::CheckPoolsEmpty() {
    plugin::Call<0x551950>();
}

// 0x550050
CObject* CPools::GetObject(int32 handle) {
    return plugin::CallAndReturn<CObject*, 0x550050, int32>(handle);
}

// 0x550020
int32 CPools::GetObjectRef(CObject* object) {
    return plugin::CallAndReturn<int32, 0x550020, CObject*>(object);
}

// 0x54FF90
CPed* CPools::GetPed(int32 handle) {
    return plugin::CallAndReturn<CPed*, 0x54FF90, int32>(handle);
}

// 0x54FF60
int32 CPools::GetPedRef(CPed* ped) {
    return plugin::CallAndReturn<int32, 0x54FF60, CPed*>(ped);
}

// 0x54FFF0
CVehicle* CPools::GetVehicle(int32 handle) {
    return plugin::CallAndReturn<CVehicle*, 0x54FFF0, int32>(handle);
}

// 0x54FFC0
int32 CPools::GetVehicleRef(CVehicle* vehicle) {
    return plugin::CallAndReturn<int32, 0x54FFC0, CVehicle*>(vehicle);
}

// 0x550F10
void CPools::Initialise() {
    plugin::Call<0x550F10>();
}

// 0x5D0890
bool CPools::Load() {
    return plugin::CallAndReturn<bool, 0x5D0890>();
}

// 0x5D4A40
bool CPools::LoadObjectPool() {
    int32 iNumObjects = 0;
    CGenericGameStorage::LoadDataFromWorkBuffer(&iNumObjects, 4);
    for (int32 i = 0; i < iNumObjects; ++i)
    {
        int32 iPoolRef = 0, iModelId = 0;
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

// 0x5D2D70
bool CPools::LoadPedPool() {
    return plugin::CallAndReturn<bool, 0x5D2D70>();
}

// 0x5D2A20
bool CPools::LoadVehiclePool() {
    return plugin::CallAndReturn<bool, 0x5D2A20>();
}

// 0x550080
void CPools::MakeSureSlotInObjectPoolIsEmpty(int32 slot) {
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

// 0x5D0880
bool CPools::Save() {
    return plugin::CallAndReturn<bool, 0x5D0880>();
}

// 0x5D4940
bool CPools::SaveObjectPool() {
    return plugin::CallAndReturn<bool, 0x5D4940>();
}

// 0x5D4B40
bool CPools::SavePedPool() {
    return plugin::CallAndReturn<bool, 0x5D4B40>();
}

// 0x5D4800
bool CPools::SaveVehiclePool() {
    return plugin::CallAndReturn<bool, 0x5D4800>();
}

// 0x5519F0
void CPools::ShutDown() {
    plugin::Call<0x5519F0>();
}
