#include "StdInc.h"

void CDummyObject::InjectHooks()
{
    Install("CDummyObject", "CreateObject", 0x59EAC0, &CDummyObject::CreateObject);
    Install("CDummyObject", "UpdateFromObject", 0x59EB70, &CDummyObject::UpdateFromObject);
}

CDummyObject::CDummyObject(CObject* pObj) : CDummy()
{
    CEntity::SetModelIndexNoCreate(m_nModelIndex);
    if (pObj->m_pRwObject)
        CEntity::AttachToRwObject(pObj->m_pRwObject, true);

    pObj->DetachFromRwObject();
    m_nIplIndex = pObj->m_nIplIndex;
    m_nAreaCode = pObj->m_nAreaCode;
    CIplStore::IncludeEntity(m_nIplIndex, this);
}

CObject* CDummyObject::CreateObject()
{
    m_bImBeingRendered = true; //BUG? Seems like that flag doesn't fit here
    auto* pObj = CObject::Create(this);
    m_bImBeingRendered = false;

    if (pObj)
    {
        CTheScripts::ScriptsForBrains.CheckIfNewEntityNeedsScript(pObj, 1, nullptr);
        m_bIsVisible = false;
        m_bUsesCollision = false;

        pObj->m_nLodIndex = m_nLodIndex;
        m_nLodIndex = 0;
    }

    return pObj;
}

void CDummyObject::UpdateFromObject(CObject* pObject)
{
    m_bIsVisible = true;
    m_bUsesCollision = true;

    pObject->m_bImBeingRendered = true;
    CEntity::AttachToRwObject(pObject->m_pRwObject, false);
    pObject->m_bImBeingRendered = false;
    CEntity::UpdateRW();
    pObject->DetachFromRwObject();

    if (pObject->m_nIplIndex && CIplStore::HasDynamicStreamingDisabled(pObject->m_nIplIndex))
    {
        m_bRenderDamaged = pObject->m_bRenderDamaged;
        m_bIsVisible = pObject->m_bIsVisible;
        m_bUsesCollision = pObject->m_bUsesCollision;
    }

    m_nLodIndex = pObject->m_nLodIndex;
    pObject->m_nLodIndex = 0;

}
