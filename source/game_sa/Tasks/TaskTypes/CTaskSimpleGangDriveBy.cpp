#include "StdInc.h"

CTaskSimpleGangDriveBy::CTaskSimpleGangDriveBy(CEntity* target, const CVector* targetPos, float abortRange,
    std::int8_t frequencyPercentage, std::int8_t drivebyStyle, bool seatRHS)
{
    m_bSeatRHS = seatRHS;
    m_nDrivebyStyle = drivebyStyle;
    m_fAbortRange = abortRange;
    m_pTargetEntity = target;
    m_nFrequencyPercentage = frequencyPercentage;
    m_bIsFinished = 0;
    m_bAnimsReferenced = 0;
    m_bInRangeToShoot = 0;
    m_bInWeaponRange = 0;
    m_bReachedAbortRange = 0;
    m_bFromScriptCommand = 0;
    m_nBurstShots = -1;
    m_nFakeShootDirn = -1;
    m_nAttackTimer = -1;
    m_nLastCommand = 0;
    m_nNextCommand = 1;
    m_nLOSCheckTime = 0;
    m_nLOSBlocked = 1;
    m_pAnimAssoc = 0;
    m_nRequiredAnimID = ANIM_ID_NO_ANIMATION_SET;
    m_nRequiredAnimGroup = 0;
    m_pWeaponInfo = 0;
    if (m_pTargetEntity)
        m_pTargetEntity->RegisterReference(&m_pTargetEntity);
    if (targetPos)
        m_vecCoords = *targetPos;
}

CTaskSimpleGangDriveBy::~CTaskSimpleGangDriveBy()
{
    if (m_bAnimsReferenced)
        CAnimManager::RemoveAnimBlockRef(CAnimManager::GetAnimationBlockIndex(m_nRequiredAnimGroup));
    if (m_pAnimAssoc)
        m_pAnimAssoc->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, 0);
    if (m_pTargetEntity)
        m_pTargetEntity->CleanUpOldReference(&m_pTargetEntity);
}

CTask* CTaskSimpleGangDriveBy::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x6236D0, CTask*>(this);
}

bool CTaskSimpleGangDriveBy::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    return plugin::CallMethodAndReturn<bool, 0x62D290, CTask*, CPed*, int, CEvent*>(this, ped, priority, _event);
}

bool CTaskSimpleGangDriveBy::ProcessPed(CPed* ped)
{
    return plugin::CallMethodAndReturn<bool, 0x62D3B0, CTask*, CPed*>(this, ped);
}
