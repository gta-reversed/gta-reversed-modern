#include "StdInc.h"

#include "PlantColEntEntry.h"
#include "PlantMgr.h"

void CPlantColEntEntry::InjectHooks() {
    RH_ScopedClass(CPlantColEntEntry);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(AddEntry, 0x5DB7D0);
    RH_ScopedInstall(ReleaseEntry, 0x5DB8A0, {.reversed = false});
}

// 0x5DB7D0
CPlantColEntEntry* CPlantColEntEntry::AddEntry(CEntity* entity) {
    //return plugin::CallMethodAndReturn<CPlantColEntEntry*, 0x5DB7D0, CPlantColEntEntry*, CEntity*>(this, entity);
    m_Entity = entity;
    entity->RegisterReference(&m_Entity);

    auto colData = entity->GetColData();
    if (!colData || colData->m_nNumTriangles < 1) {
        return nullptr;
    }
    m_numTriangles = colData->m_nNumTriangles;
    m_Objects = CMemoryMgr::Calloc<CPlantLocTri**>(m_numTriangles, sizeof(CPlantLocTri*)); // originally Malloc zeroed afterwards

    if (m_NextEntry) {
        if (m_PrevEntry) {
            m_PrevEntry->m_NextEntry = m_NextEntry;
            m_NextEntry->m_PrevEntry = m_PrevEntry;
        } else {
            m_NextEntry->m_PrevEntry = nullptr;
        }
    } else {
        CPlantMgr::m_UnusedColEntListHead = m_PrevEntry;
        if (m_PrevEntry) {
            CPlantMgr::m_UnusedColEntListHead->m_NextEntry = nullptr;
        }
    }
    m_PrevEntry = CPlantMgr::m_CloseColEntListHead;
    m_NextEntry = nullptr;
    CPlantMgr::m_CloseColEntListHead = this;

    if (m_PrevEntry) {
        m_PrevEntry->m_NextEntry = this;
    }

    return this;
}

// 0x5DB8A0
void CPlantColEntEntry::ReleaseEntry() {
    plugin::CallMethod<0x5DB7D0, CPlantColEntEntry*>(this);
}
