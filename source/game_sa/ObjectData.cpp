#include "StdInc.h"

CObjectData(&CObjectData::ms_aObjectInfo)[NUM_OBJECT_INFOS] = *(CObjectData(*)[NUM_OBJECT_INFOS])0xBB4A90;

void CObjectData::InjectHooks()
{
    RH_ScopedInstall(Initialise, 0x5B5360);
    RH_ScopedInstall(SetObjectData, 0x5A2D00);
}

// 0x5B5360
void CObjectData::Initialise(const char* fileName)
{
    auto& pDefault = CObjectData::GetDefault();
    pDefault.m_fMass = 99999.0F;
    pDefault.m_fTurnMass = 99999.0F;
    pDefault.m_fAirResistance = 0.99F;
    pDefault.m_fElasticity = 0.1F;
    pDefault.m_fBuoyancyConstant = 1599.9841F;
    pDefault.m_fUprootLimit = 0.0F;
    pDefault.m_fColDamageMultiplier = 1.0F;
    pDefault.m_nColDamageEffect = eObjectColDamageEffect::COL_DAMAGE_EFFECT_NONE;
    pDefault.m_nSpecialColResponseCase = eObjectSpecialColResponseCases::COL_SPECIAL_RESPONSE_NONE;
    pDefault.m_nCameraAvoidObject = eObjectCameraAvoidType::CAMERA_UNKNOWN;

    auto& pDefault1 = CObjectData::GetAtIndex(1);
    pDefault1 = pDefault;
    pDefault1.m_nCameraAvoidObject = eObjectCameraAvoidType::CAMERA_IGNORE;

    auto& pDefault2 = CObjectData::GetAtIndex(2);
    pDefault2 = pDefault;
    pDefault2.m_nSpecialColResponseCase = eObjectSpecialColResponseCases::COL_SPECIAL_RESPONSE_FENCEPART;

    auto& pDefault3 = CObjectData::GetAtIndex(3);
    pDefault3 = pDefault;
    pDefault3.m_nCameraAvoidObject = eObjectCameraAvoidType::CAMERA_IGNORE;
    pDefault3.m_nSpecialColResponseCase = eObjectSpecialColResponseCases::COL_SPECIAL_RESPONSE_FENCEPART;

    auto& pDefault4 = CObjectData::GetAtIndex(4);
    pDefault4 = pDefault;
    pDefault4.m_nSpecialColResponseCase = eObjectSpecialColResponseCases::COL_SPECIAL_RESPONSE_GRENADE;

    CFileMgr::SetDir(gta_empty_string);
    auto* pFile = CFileMgr::OpenFile(fileName, "rb");
    char* pLine;
    auto iFirstFreeInd = 5;
    while((pLine = CFileLoader::LoadLine(pFile)))
    {
        if (!pLine[0] || pLine[0] == ';')
            continue;

        if (pLine[0] == '*')
            break;

        auto& pCurInfo = CObjectData::GetAtIndex(iFirstFreeInd);
        memset(&pCurInfo, 0, sizeof(CObjectData));
        char modelName[256], effectName[256];
        float fPercentSubmerged;
        int32 iColDamEffect, iSpecialColResp, iCameraAvoid, iCausesExplosion, iFxType; // Have to be read as 32-bit integers and later assigned to 8 bit int32
        sscanf(pLine, "%s %f %f %f %f %f %f %f %d %d %d %d %d %f %f %f %s %f %f %f %f %f %d %d",
            modelName,
            &pCurInfo.m_fMass,
            &pCurInfo.m_fTurnMass,
            &pCurInfo.m_fAirResistance,
            &pCurInfo.m_fElasticity,
            &fPercentSubmerged,
            &pCurInfo.m_fUprootLimit,
            &pCurInfo.m_fColDamageMultiplier,
            &iColDamEffect,
            &iSpecialColResp,
            &iCameraAvoid,
            &iCausesExplosion,
            &iFxType,
            &pCurInfo.m_vFxOffset.x,
            &pCurInfo.m_vFxOffset.y,
            &pCurInfo.m_vFxOffset.z,
            effectName,
            &pCurInfo.m_fSmashMultiplier,
            &pCurInfo.m_vecBreakVelocity.x,
            &pCurInfo.m_vecBreakVelocity.y,
            &pCurInfo.m_vecBreakVelocity.z,
            &pCurInfo.m_fBreakVelocityRand,
            &pCurInfo.m_nGunBreakMode,
            &pCurInfo.m_nSparksOnImpact);

        pCurInfo.m_pFxSystemBP = nullptr;
        pCurInfo.m_nFxType = iFxType;
        if (iFxType > 0)
            pCurInfo.m_pFxSystemBP = g_fxMan.FindFxSystemBP(effectName);

        const auto fBuoyancy = (100.0F / fPercentSubmerged) * (pCurInfo.m_fMass / 125.0F);
        pCurInfo.m_nSpecialColResponseCase = iSpecialColResp;
        pCurInfo.m_nColDamageEffect = iColDamEffect;
        pCurInfo.m_nCameraAvoidObject = iCameraAvoid;
        pCurInfo.m_bCausesExplosion = iCausesExplosion;
        pCurInfo.m_fBuoyancyConstant = fBuoyancy;

        auto *pModelInfo = CModelInfo::GetModelInfo(modelName, nullptr);
        if (!pModelInfo)
            continue;

        if (pCurInfo.m_fMass == pDefault.m_fMass
            && pCurInfo.m_fColDamageMultiplier == pDefault.m_fColDamageMultiplier
            && pCurInfo.m_nColDamageEffect == pDefault.m_nColDamageEffect)
        {
            if (pCurInfo.m_nSpecialColResponseCase == pDefault.m_nSpecialColResponseCase)
            {
                pModelInfo->m_nObjectInfoIndex = pCurInfo.m_nCameraAvoidObject == 0 ? 0 : 1;
                continue;
            }

            if (pCurInfo.m_nSpecialColResponseCase == pDefault2.m_nSpecialColResponseCase)
            {
                pModelInfo->m_nObjectInfoIndex = pCurInfo.m_nCameraAvoidObject == 0 ? 2 : 3;
                continue;
            }
        }

        int32 iCheckedInd = 0;
        bool bFound = false;
        while (iCheckedInd < iFirstFreeInd)
        {
            if (pCurInfo == CObjectData::GetAtIndex(iCheckedInd))
            {
                pModelInfo->m_nObjectInfoIndex = iCheckedInd;
                bFound = true;
                break;
            }

            ++iCheckedInd;
        }

        if (bFound)
            continue;

        pModelInfo->m_nObjectInfoIndex = iFirstFreeInd;
        ++iFirstFreeInd;
    }

    CFileMgr::CloseFile(pFile);
}

// 0x5A2D00
void CObjectData::SetObjectData(int32 dwModelIndex, CObject& pObject)
{
    auto* const pModelInfo = CModelInfo::GetModelInfo(dwModelIndex);
    if (pModelInfo->m_nObjectInfoIndex == -1)
    {
        pObject.m_fMass = 99999.0F;
        pObject.m_fTurnMass = 99999.0F;

        pObject.physicalFlags.bApplyGravity = false;
        pObject.physicalFlags.bExplosionProof = true;
        pObject.physicalFlags.bCollidable = true;
        pObject.physicalFlags.bDisableCollisionForce = true;

        pObject.m_pObjectInfo = &CObjectData::GetDefault();
        return;
    }

    auto& pObjInfo = CObjectData::GetAtIndex(pModelInfo->m_nObjectInfoIndex);
    pObject.m_pObjectInfo = &pObjInfo;
    pObject.m_fMass = pObjInfo.m_fMass;
    pObject.m_fTurnMass = pObjInfo.m_fTurnMass;
    pObject.m_fAirResistance = pObjInfo.m_fAirResistance;
    pObject.m_fElasticity = pObjInfo.m_fElasticity;
    pObject.m_fBuoyancyConstant = pObjInfo.m_fBuoyancyConstant;
    pObject.m_nColDamageEffect = pObjInfo.m_nColDamageEffect;

    if (pObjInfo.m_fMass >= 99998.0F)
    {
        pObject.physicalFlags.bApplyGravity = false;
        pObject.physicalFlags.bCollidable = true;
        pObject.physicalFlags.bDisableCollisionForce = true;

        if (pObjInfo.m_nColDamageEffect == eObjectColDamageEffect::COL_DAMAGE_EFFECT_NONE)
            pObject.physicalFlags.bExplosionProof = true;
    }

    switch(pObjInfo.m_nSpecialColResponseCase)
    {
    case eObjectSpecialColResponseCases::COL_SPECIAL_RESPONSE_SWINGDOOR:
        pObject.physicalFlags.bDisableMoveForce = true;
        pObject.objectFlags.bIsDoorOpen = false;
        pObject.objectFlags.bIsDoorMoving = false;
        break;
    case eObjectSpecialColResponseCases::COL_SPECIAL_RESPONSE_LOCKDOOR:
        pObject.physicalFlags.bDisableMoveForce = true;
        pObject.physicalFlags.bCollidable = true;
        pObject.physicalFlags.bDisableCollisionForce = true;
        pObject.objectFlags.bIsDoorOpen = false;
        pObject.objectFlags.bIsDoorMoving = true;
        break;
    case eObjectSpecialColResponseCases::COL_SPECIAL_RESPONSE_HANGING:
        pObject.physicalFlags.bInfiniteMass = true;
        pObject.m_vecCentreOfMass.Set(0.0F, 0.0F, pModelInfo->GetColModel()->GetBoundingBox().m_vecMin.z * 0.8F);
        break;
    case eObjectSpecialColResponseCases::COL_SPECIAL_RESPONSE_OB_COL_POOLBALL:
        pObject.physicalFlags.bApplyGravity = false;
        pObject.physicalFlags.bDisableZ = true;
        break;
    }
}

bool CObjectData::operator==(CObjectData const& right) const
{
    return m_fMass == right.m_fMass
        && m_fTurnMass == right.m_fTurnMass
        && m_fAirResistance == right.m_fAirResistance
        && m_fElasticity == right.m_fElasticity
        && m_fBuoyancyConstant == right.m_fBuoyancyConstant
        && m_fUprootLimit == right.m_fUprootLimit
        && m_fColDamageMultiplier == right.m_fColDamageMultiplier
        && m_nColDamageEffect == right.m_nColDamageEffect
        && m_nSpecialColResponseCase == right.m_nSpecialColResponseCase
        && m_nCameraAvoidObject == right.m_nCameraAvoidObject
        && m_bCausesExplosion == right.m_bCausesExplosion
        && m_nFxType == right.m_nFxType
        && m_vFxOffset == right.m_vFxOffset
        && m_pFxSystemBP == right.m_pFxSystemBP
        && m_fSmashMultiplier == right.m_fSmashMultiplier
        && m_vecBreakVelocity == right.m_vecBreakVelocity
        && m_fBreakVelocityRand == right.m_fBreakVelocityRand
        && m_nGunBreakMode == right.m_nGunBreakMode
        && m_nSparksOnImpact == right.m_nSparksOnImpact;

}

