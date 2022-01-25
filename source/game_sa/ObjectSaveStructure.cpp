#include "StdInc.h"

void CObjectSaveStructure::InjectHooks()
{
    Install("CObjectSaveStructure", "Construct", 0x5D2160, &CObjectSaveStructure::Construct);
    Install("CObjectSaveStructure", "Extract", 0x5D2220, &CObjectSaveStructure::Extract);
}

void CObjectSaveStructure::Construct(CObject* pObject)
{
    m_matrix.CompressFromFullMatrix(*pObject->m_matrix);
    m_nBonusValue  = pObject->m_nBonusValue;
    m_nCostValue   = pObject->m_wCostValue;
    m_nRemovalTime = pObject->m_dwRemovalTime;
    m_nEntityFlags = pObject->m_nFlags;
    m_nObjectFlags = pObject->m_nObjectFlags;
    m_nObjectType  = pObject->m_nObjectType;
    m_nColDamageEffect = pObject->m_nColDamageEffect;
    m_nSpecialColResponseCase = pObject->m_nSpecialColResponseCase;
    m_nUnused = 0;

    m_nPhysicalFlags = 0;

    if (pObject->physicalFlags.bDisableCollisionForce)
        m_bDisableCollisionForce = true;

    if (pObject->physicalFlags.bDontApplySpeed)
        m_bDontApplySpeed = true;

    if (pObject->physicalFlags.bBulletProof)
        m_bBulletProof = true;

    if (pObject->physicalFlags.bFireProof)
        m_bFireProof = true;

    if (pObject->physicalFlags.bCollisionProof)
        m_bCollisionProof = true;

    if (pObject->physicalFlags.bMeeleProof)
        m_bMeeleProof = true;

    if (pObject->physicalFlags.bExplosionProof)
        m_bExplosionProof = true;
}

void CObjectSaveStructure::Extract(CObject* pObject)
{
    m_matrix.DecompressIntoFullMatrix(*pObject->m_matrix);
    pObject->m_nBonusValue = m_nBonusValue;
    pObject->m_wCostValue = m_nCostValue;
    pObject->m_dwRemovalTime = m_nRemovalTime;
    pObject->m_nFlags = m_nEntityFlags;
    pObject->m_nObjectFlags = m_nObjectFlags;
    pObject->m_nObjectType = m_nObjectType;
    pObject->m_nColDamageEffect = m_nColDamageEffect;
    pObject->m_nSpecialColResponseCase = m_nSpecialColResponseCase;

    pObject->physicalFlags.bDisableCollisionForce = m_bDisableCollisionForce;
    pObject->physicalFlags.bDontApplySpeed = m_bDontApplySpeed;
    pObject->physicalFlags.bBulletProof = m_bBulletProof;
    pObject->physicalFlags.bFireProof = m_bFireProof;
    pObject->physicalFlags.bCollisionProof = m_bCollisionProof;
    pObject->physicalFlags.bMeeleProof = m_bMeeleProof;
    pObject->physicalFlags.bExplosionProof = m_bExplosionProof;
}
