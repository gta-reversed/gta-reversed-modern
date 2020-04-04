#include "StdInc.h"

CTask* CTaskSimpleHoldEntity::Clone()
{
    return plugin::CallMethodAndReturn<CTaskSimpleHoldEntity*, 0x6929B0, CTaskSimpleHoldEntity*>(this);
}

eTaskType CTaskSimpleHoldEntity::GetId() 
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<eTaskType, 0x691460, CTaskSimpleHoldEntity*>(this);
#else
    return GetId_Reversed();
#endif
}

bool CTaskSimpleHoldEntity::MakeAbortable(class CPed* ped, eAbortPriority priority, class CEvent* _event)
{
    return plugin::CallMethodAndReturn<bool, 0x693BD0, CTaskSimpleHoldEntity*, CPed*, eAbortPriority, CEvent*>(this, ped, priority, _event);
}

bool CTaskSimpleHoldEntity::ProcessPed(class CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x693C40, CTaskSimpleHoldEntity*, CPed*>(this, ped);
#else
    return ProcessPed_Reversed(ped);
#endif
}

bool CTaskSimpleHoldEntity::SetPedPosition(class CPed* ped)
{
    return plugin::CallMethodAndReturn<bool, 0x6940A0, CTaskSimpleHoldEntity*, CPed*>(this, ped);
}

eTaskType CTaskSimpleHoldEntity::GetId_Reversed()
{
    return TASK_SIMPLE_HOLD_ENTITY;
}

bool CTaskSimpleHoldEntity::ProcessPed_Reversed(class CPed* ped)
{
    CTaskManager* pTaskManager = &ped->m_pIntelligence->m_TaskMgr;
    if (m_bEntityRequiresProcessing)
    {
        m_bEntityRequiresProcessing = 0;
        if (GetId() == TASK_SIMPLE_PUTDOWN_ENTITY && !m_pEntityToHold && !m_pAnimBlendHierarchy && !m_nAnimGroupId)
        {
            auto pHoldEntityTask = (CTaskSimpleHoldEntity*)pTaskManager->GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
            if (pHoldEntityTask && pHoldEntityTask->GetId() == TASK_SIMPLE_HOLD_ENTITY &&
                pHoldEntityTask->m_pEntityToHold && pHoldEntityTask->m_nAnimGroupId)
            {
                CEntity* pEntitToHold = pHoldEntityTask->m_pEntityToHold;
                m_pEntityToHold = pEntitToHold;
                pEntitToHold->RegisterReference(&m_pEntityToHold);

                m_vecPosition = pHoldEntityTask->m_vecPosition;
                m_nAnimId = CARRY_PUTDWN;
                m_nAnimGroupId = pHoldEntityTask->m_nAnimGroupId;
                ChoosePutDownHeight(ped);
                pHoldEntityTask->ReleaseEntity();
            }
            else
            {
                m_bEntityDropped = 1;
            }
        }
        CEntity* pEntitToHold = m_pEntityToHold;
        if (!pEntitToHold || m_bEntityDropped)
        {
            m_bEntityDropped = 1;
        }
        else
        {
            pEntitToHold->m_bUsesCollision = 0;
            if (pEntitToHold->m_nType == ENTITY_TYPE_OBJECT)
            {
                CObject* pObjecToHold = (CObject*)pEntitToHold;
                if (pObjecToHold->m_bIsStatic || pObjecToHold->m_bIsStaticWaitingForCollision)
                {
                    pObjecToHold->SetIsStatic(false);
                    pObjecToHold->AddToMovingList();
                }

                pObjecToHold->physicalFlags.bAttachedToEntity = 1;
                pObjecToHold->m_bFakePhysics = 0;
            }

            float fRotation = pEntitToHold->m_placement.m_fHeading - ped->m_fCurrentRotation;;
            CMatrixLink* pEntityToHoldMatrix = pEntitToHold->m_matrix;
            if (pEntityToHoldMatrix)
            {
                fRotation = atan2(-pEntityToHoldMatrix->up.x, pEntityToHoldMatrix->up.y) - ped->m_fCurrentRotation;
            }

            m_fRotation = fRotation;
        }
    }

    if (m_bEntityDropped)
    {
        return true;
    }

    if (m_nAnimId != NO_ANIMATION_SET || m_pAnimBlendHierarchy)
    {
        auto pAnimBlendAssoc = m_pAnimBlendAssociation;
        if (pAnimBlendAssoc)
        {
            if (pAnimBlendAssoc->m_fBlendDelta < 0.0 && !m_bDisallowDroppingOnAnimEnd)
            {
                DropEntity(ped, true);
            }
        }
        else
        {
            StartAnim(ped);
        }
    }

    if (m_pEntityToHold)
    {
        CEntity* pEntityToHold = m_pEntityToHold;
        eTaskType taskId = GetId();
        if (taskId != TASK_SIMPLE_HOLD_ENTITY)
        {
            if (taskId != TASK_SIMPLE_PICKUP_ENTITY)
            {
                auto pTaskHoldEntity = (CTaskSimpleHoldEntity*)pTaskManager->GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
                if (pTaskHoldEntity && pTaskHoldEntity->GetId() == TASK_SIMPLE_HOLD_ENTITY)
                {
                    pTaskHoldEntity->MakeAbortable(ped, ABORT_PRIORITY_URGENT, 0);
                }
            }
            else
            {
                auto pTaskPickUpEntity = (CTaskSimplePickUpEntity*)this;
                auto pAnimAssoc = pTaskPickUpEntity->m_pAnimBlendAssociation;
                if ((!pAnimAssoc || pTaskPickUpEntity->m_fMovePedUntilAnimProgress > pAnimAssoc->m_fCurrentTime)
                    && (pTaskPickUpEntity->m_vecPickupPosition.x != 0.0 || pTaskPickUpEntity->m_vecPickupPosition.y != 0.0))
                {
                    CVector outPoint;
                    MultiplyMatrixWithVector(&outPoint, pEntityToHold->GetMatrix(), &pTaskPickUpEntity->m_vecPickupPosition);

                    CVector* pPedPos = &ped->m_placement.m_vPosn;
                    CMatrixLink* pPedMatrix = ped->m_matrix;
                    if (pPedMatrix)
                    {
                        pPedPos = &pPedMatrix->pos;
                    }

                    outPoint.x = outPoint.x - pPedPos->x;
                    outPoint.y = outPoint.y - pPedPos->y;
                    outPoint.z = outPoint.z - pPedPos->z;

                    ped->m_vecAnimMovingShiftLocal.x = (
                        outPoint.z * pPedMatrix->right.z
                        + outPoint.y * pPedMatrix->right.y
                        + outPoint.x * pPedMatrix->right.x)
                        / CTimer::ms_fTimeStep * 0.1f + ped->m_vecAnimMovingShiftLocal.x;

                    ped->m_vecAnimMovingShiftLocal.y = (outPoint.z * pPedMatrix->up.z
                        + outPoint.y * pPedMatrix->up.y
                        + outPoint.x * pPedMatrix->up.x)
                        / CTimer::ms_fTimeStep * 0.1f + ped->m_vecAnimMovingShiftLocal.y;


                    CVector* pEntityToHoldPos = &pEntityToHold->m_placement.m_vPosn;
                    CMatrixLink* pEntityToHoldMatrix = pEntityToHold->m_matrix;
                    if (pEntityToHoldMatrix)
                    {
                        pEntityToHoldPos = &pEntityToHoldMatrix->pos;
                    }

                    VectorSub(&outPoint, pEntityToHoldPos, pPedPos);
                    ped->m_fAimingRotation = atan2(-outPoint.x, outPoint.y);
                }
            }
        }
        else
        {
            int animGroup = m_nAnimGroupId;
            if ((animGroup == ANIM_GROUP_CARRY || animGroup == ANIM_GROUP_CARRY05 || animGroup == ANIM_GROUP_CARRY105) && ped->IsPlayer())
            {
                CPlayerPed* pPlayer = (CPlayerPed*)ped;
                CPad* pPad = pPlayer->GetPadFromPlayer();
                if (pPad->ExitVehicleJustDown())
                {
                    auto pTaskSimplePutDownEntity = (CTaskSimplePutDownEntity*)CTask::operator new(64);
                    if (pTaskSimplePutDownEntity)
                    {
                        pTaskSimplePutDownEntity->Constructor();
                    }

                    CEventScriptCommand eventScriptCommand;
                    eventScriptCommand.Constructor(3, pTaskSimplePutDownEntity, 0);
                    CEventGroup* pEventGroup = &ped->m_pIntelligence->m_eventGroup;
                    pEventGroup->Add(&eventScriptCommand, 0);
                    eventScriptCommand.Destructor();
                }
            }
        }
    }
    return false;
}

CTaskSimpleHoldEntity* CTaskSimpleHoldEntity::Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
    int animId, int groupId, bool bDisAllowDroppingOnAnimEnd)
{
    return plugin::CallMethodAndReturn<CTaskSimpleHoldEntity*, 0x6913A0, CTaskSimpleHoldEntity*, CEntity*, CVector*, char, unsigned char,
        int, int, bool>(this, pEntityToHold, pPosition, boneFrameId, boneFlags, animId, groupId, bDisAllowDroppingOnAnimEnd);
}

CTaskSimpleHoldEntity* CTaskSimpleHoldEntity::Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
    char* pAnimName, int animBlockId, int animFlags)
{
    return plugin::CallMethodAndReturn<CTaskSimpleHoldEntity*, 0x691470, CTaskSimpleHoldEntity*, CEntity*, CVector*, char, unsigned char,
        char*, int, int>(this, pEntityToHold, pPosition, boneFrameId, boneFlags, pAnimName, animBlockId, animFlags);
}

CTaskSimpleHoldEntity* CTaskSimpleHoldEntity::Constructor(CEntity* pEntityToHold, CVector* pPosition, char boneFrameId, unsigned char boneFlags,
    CAnimBlock* pAnimBlock, CAnimBlendHierarchy* pAnimHierarchy, int animFlags)
{
    return plugin::CallMethodAndReturn<CTaskSimpleHoldEntity*, 0x691550, CTaskSimpleHoldEntity*, CEntity*, CVector*, char, unsigned char,
        CAnimBlock*, CAnimBlendHierarchy*, int>(this, pEntityToHold, pPosition, boneFrameId, boneFlags, pAnimBlock, pAnimHierarchy, animFlags);
}

CTaskSimpleHoldEntity* CTaskSimpleHoldEntity::Destructor()
{
    return plugin::CallMethodAndReturn<CTaskSimpleHoldEntity*, 0x691630, CTaskSimpleHoldEntity*>(this);
}

void CTaskSimpleHoldEntity::ReleaseEntity()
{
    plugin::CallMethod<0x6916E0, CTaskSimpleHoldEntity*>(this);
}

bool CTaskSimpleHoldEntity::CanThrowEntity()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x0, CTaskSimpleHoldEntity*>(this);
#else
    return m_pEntityToHold && m_bBoneFlags == HOLD_ENTITY_UPDATE_BONE_TRANSLATION_ONLY && m_bBoneFrameId == 6;
#endif
}

void CTaskSimpleHoldEntity::PlayAnim(int groupId, int animId)
{
    plugin::CallMethod<0x691720, CTaskSimpleHoldEntity*, int, int>(this, groupId, animId);
}

void CTaskSimpleHoldEntity::FinishAnimHoldEntityCB(CAnimBlendAssociation* pAnimAssoc, CTaskSimpleHoldEntity* pTaskHoldEntity)
{
    plugin::Call<0x691740, CAnimBlendAssociation*, CTaskSimpleHoldEntity*>(pAnimAssoc, pTaskHoldEntity);
}

void CTaskSimpleHoldEntity::StartAnim(CPed* pPed)
{
    plugin::CallMethod<0x692FF0, CTaskSimpleHoldEntity*, CPed*>(this, pPed);
}

void CTaskSimpleHoldEntity::DropEntity(CPed* pPed, bool bAddEventSoundQuiet)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x6930F0, CTaskSimpleHoldEntity*, CPed*, bool>(this, pPed, bAddEventSoundQuiet);
#else
    bool bUpdateEntityPosition = true;
    CObject* pObjectToHold = nullptr;
    if (m_pEntityToHold)
    {
        m_pEntityToHold->m_bUsesCollision = 1;
        if (m_pEntityToHold->m_nType != ENTITY_TYPE_OBJECT)
        {
            m_pEntityToHold->CleanUpOldReference(&m_pEntityToHold);
            m_pEntityToHold = 0;
            return;
        }

        pObjectToHold = (CObject*)m_pEntityToHold;
        CVector* pVecMoveSpeed = &pObjectToHold->m_vecMoveSpeed;
        pObjectToHold->m_pEntityIgnoredCollision = pPed;
        if (pObjectToHold->physicalFlags.bDisableCollisionForce && bAddEventSoundQuiet)
        {
            if (!pObjectToHold->objectFlags.bIsLiftable)
            {
                unsigned char objectType = pObjectToHold->m_nObjectType;
                if (objectType != OBJECT_MISSION && objectType != OBJECT_MISSION2)
                {
                    if (objectType != OBJECT_TEMPORARY)
                    {
                        ++CObject::nNoTempObjects;
                    }
                    pObjectToHold->m_nObjectType = OBJECT_TEMPORARY;
                    pObjectToHold->m_dwRemovalTime = 0;
                    pObjectToHold->m_bUsesCollision = 0;
                    bUpdateEntityPosition = false;
                }
            }
        }
        else
        {
            pObjectToHold->physicalFlags.bAttachedToEntity = 0;
            if (!bAddEventSoundQuiet)
            {
                bUpdateEntityPosition = false;
            }
            else
            {
                if (pObjectToHold->m_bIsStatic || pObjectToHold->m_bIsStaticWaitingForCollision)
                {
                    pObjectToHold->SetIsStatic(false);
                    pObjectToHold->AddToMovingList();
                }

                *pVecMoveSpeed = pPed->m_vecMoveSpeed;
                CMatrixLink* pPedMatrix = pPed->m_matrix;
                float randomSpeedUp = rand() * 4.6566e-10f * 0.03f + 0.03f;
                pVecMoveSpeed->x += randomSpeedUp * pPedMatrix->up.x;
                pVecMoveSpeed->y += randomSpeedUp * pPedMatrix->up.y;
                pVecMoveSpeed->z += randomSpeedUp * pPedMatrix->up.z;
                float randomSpeedRight = rand() * 4.6566e-10f * 0.06f - 0.03f;
                pVecMoveSpeed->x += randomSpeedRight * pPedMatrix->right.x;
                pVecMoveSpeed->y += randomSpeedRight * pPedMatrix->right.y;
                pVecMoveSpeed->z += randomSpeedRight * pPedMatrix->right.z;
                pVecMoveSpeed->x = pPedMatrix->at.x * 0.01f;
                pVecMoveSpeed->y += pPedMatrix->at.y * 0.01f;
                pVecMoveSpeed->z += pPedMatrix->at.z * 0.01f;
                if (!pObjectToHold->TestCollision(false))
                {
                    bUpdateEntityPosition = false;
                }
            }
        }

        CVector objectToHoldPosition(0.0f, 0.0f, 0.0f);
        if (pObjectToHold->objectFlags.bIsLiftable && pPed->m_pPlayerData && bAddEventSoundQuiet)
        {
            CEventSoundQuiet eventSoundQuiet;
            eventSoundQuiet.Constructor(pPed, 60.0f, -1, &objectToHoldPosition);
            CEventGroup* pEventGroup = GetEventGlobalGroup();
            pEventGroup->Add(&eventSoundQuiet, 0);
            eventSoundQuiet.Destructor();
        }

        if (bUpdateEntityPosition)
        {
            *pVecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);

            pObjectToHold->SetIsStatic(1);
            pObjectToHold->RemoveFromMovingList();

            CVector* pPedPos = &pPed->m_placement.m_vPosn;
            CMatrixLink* pPedMatrix = pPed->m_matrix;
            if (pPedMatrix)
            {
                pPedPos = &pPedMatrix->pos;
            }
            CColModel* pEntityToHoldColModel = pObjectToHold->GetColModel();
            objectToHoldPosition = *pPedPos;
            objectToHoldPosition.z = objectToHoldPosition.z - 1.0f - pEntityToHoldColModel->m_boundBox.m_vecMin.z;
            pObjectToHold->SetPosn(objectToHoldPosition);
            RwObject* pRwObject = pObjectToHold->m_pRwObject;
            if (pRwObject)
            {
                RwMatrix* pRwMatrix = &((RwFrame*)pRwObject->parent)->modelling;
                CMatrixLink* pEntityToHoldMatrix = pObjectToHold->m_matrix;
                if (pEntityToHoldMatrix)
                {
                    pEntityToHoldMatrix->UpdateRwMatrix(pRwMatrix);
                }
                else
                {
                    pObjectToHold->m_placement.UpdateRwMatrix(pRwMatrix);
                }
            }
            pObjectToHold->UpdateRwFrame();
        }
        m_pEntityToHold->CleanUpOldReference(&m_pEntityToHold);
        m_pEntityToHold = 0;
        return;
    }
#endif
}

void CTaskSimpleHoldEntity::ChoosePutDownHeight(CPed* pPed)
{
    plugin::CallMethod<0x693440, CTaskSimpleHoldEntity*, CPed*>(this, pPed);
}
