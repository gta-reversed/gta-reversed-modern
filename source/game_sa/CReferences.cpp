#include "StdInc.h"

CReference(&CReferences::aRefs)[MAX_NUM_REFERENCES] = *(CReference(*)[MAX_NUM_REFERENCES])0xB9B9A8;
CReference* (&CReferences::pEmptyList) = *(CReference**)0xBA1768;

void CReferences::InjectHooks()
{
    ReversibleHooks::Install("CReferences", "Init", 0x5719B0, &CReferences::Init);
    ReversibleHooks::Install("CReferences", "ListSize", 0x5719E0, &CReferences::ListSize);
    ReversibleHooks::Install("CReferences", "RemoveReferencesToPlayer", 0x571AD0, &CReferences::RemoveReferencesToPlayer);
    ReversibleHooks::Install("CReferences", "PruneAllReferencesInWorld", 0x571CC0, &CReferences::PruneAllReferencesInWorld);
}

void CReferences::Init()
{
    CReferences::pEmptyList = CReferences::aRefs;

    for (int32_t i = 0; i < MAX_NUM_REFERENCES - 1; ++i) {
        (&CReferences::aRefs[i])->m_pNext = &CReferences::aRefs[i + 1];
        (&CReferences::aRefs[i])->m_ppEntity = nullptr;
    }

    (&CReferences::aRefs[MAX_NUM_REFERENCES - 1])->m_pNext = nullptr;
}

unsigned int CReferences::ListSize(CReference* ref)
{
    unsigned int count = 0;
    while (ref) {
        ref = ref->m_pNext;
        ++count;
    }

    return count;
}

void CReferences::RemoveReferencesToPlayer()
{
    auto pVeh = FindPlayerVehicle(-1, false);
    if (pVeh)
        pVeh->ResolveReferences();

    auto pPlayer = FindPlayerPed(-1);
    if (pPlayer) {
        pPlayer->ResolveReferences();
        auto& pGroup = CPedGroups::GetGroup(pPlayer->m_pPlayerData->m_nPlayerGroup);
        pGroup.m_groupMembership.SetLeader(pPlayer);
        pGroup.Process();
    }
}

void CReferences::PruneAllReferencesInWorld()
{
    auto iPedsSize = CPools::ms_pPedPool->GetSize();
    for (int32_t i = 0; i < iPedsSize; ++i) {
        auto pPed = CPools::ms_pPedPool->GetAt(i);
        if (pPed)
            pPed->PruneReferences();
    }

    auto iVehsSize = CPools::ms_pVehiclePool->GetSize();
    for (int32_t i = 0; i < iVehsSize; ++i) {
        auto pVeh = CPools::ms_pVehiclePool->GetAt(i);
        if (pVeh)
            pVeh->PruneReferences();
    }

    auto iObjectsSize = CPools::ms_pObjectPool->GetSize();
    for (int32_t i = 0; i < iObjectsSize; ++i) {
        auto pObj = CPools::ms_pObjectPool->GetAt(i);
        if (pObj)
            pObj->PruneReferences();
    }
}
