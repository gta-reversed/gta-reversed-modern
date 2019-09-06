#include "StdInc.h"

CTaskComplexWander* CTaskComplexWander::GetWanderTaskByPedType(CPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallAndReturn<CTaskComplexWander*, 0x673D00, CPed*>(pPed);
#else
    unsigned char randomDir = CGeneral::GetRandomNumberInRange(0, 8);
    switch (pPed->m_nPedType)
    {
    case PED_TYPE_COP:
    {
        auto pComplexWanderCop = (CTaskComplexWanderCop*)CTask::operator new(80);
        if (pComplexWanderCop)
        {
            pComplexWanderCop->Constructor(PEDMOVE_WALK, randomDir);
            return pComplexWanderCop;
        }
        break;
    }
    case PED_TYPE_GANG1:
    case PED_TYPE_GANG2:
    case PED_TYPE_GANG3:
    case PED_TYPE_GANG4:
    case PED_TYPE_GANG5:
    case PED_TYPE_GANG6:
    case PED_TYPE_GANG7:
    case PED_TYPE_GANG8:
    case PED_TYPE_GANG9:
    case PED_TYPE_GANG10:
    case PED_TYPE_DEALER:
    case PED_TYPE_FIREMAN:
    case PED_TYPE_BUM:
    {
        auto pTaskComplexWanderStandard = (CTaskComplexWanderStandard*)CTask::operator new(0x38);
        if (pTaskComplexWanderStandard)
        {
            unsigned char theRandomDir = rand() * 0.000030517578f * 8.0f;
            pTaskComplexWanderStandard->Constructor(PEDMOVE_WALK, theRandomDir, 1);
            return pTaskComplexWanderStandard;
        }
        break;
    }
    case PED_TYPE_MEDIC:
    {
        auto pTaskComplexWanderMedic = (CTaskComplexWanderMedic*)CTask::operator new(40);
        if (pTaskComplexWanderMedic)
        {
            pTaskComplexWanderMedic->Constructor(PEDMOVE_WALK, randomDir, 1);
            return pTaskComplexWanderMedic;
        }
        break;
    }
    case PED_TYPE_CRIMINAL:
    {
        auto pTaskComplexWanderCriminal = (CTaskComplexWanderCriminal*)CTask::operator new(56);
        if (pTaskComplexWanderCriminal)
        {
            pTaskComplexWanderCriminal->Constructor(PEDMOVE_WALK, randomDir, 1);
            return pTaskComplexWanderCriminal;
        }
        break;
    }
    case PED_TYPE_PROSTITUTE:
    {
        auto pTaskComplexWanderProstitute = (CTaskComplexWanderProstitute*)CTask::operator new(60);
        if (pTaskComplexWanderProstitute)
        {
            pTaskComplexWanderProstitute->Constructor(PEDMOVE_WALK, randomDir, 1);
            return pTaskComplexWanderProstitute;
        }
        break;
    }
    }
    return nullptr;
#endif
}

eTaskType CTaskComplexWander::GetId()
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return ((eTaskType(__thiscall*)(CTask*))plugin::GetVMT(this, 4))(this);
#else
    return TASK_COMPLEX_WANDER;
#endif
}

CTask* CTaskComplexWander::CreateNextSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x674140, CTaskComplexWander*, CPed*>(this, ped);
#else
    bool bTheTaskIDIs181 = false;
    int taskId = m_pSubTask->GetId();
    if (taskId > TASK_SIMPLE_SCRATCH_HEAD)
    {
        int theTaskID = taskId - TASK_COMPLEX_LEAVE_CAR;
        if (theTaskID)
        {
            theTaskID = theTaskID - 15;
            if (theTaskID)
            {
                if (theTaskID != 181)
                {
                    return nullptr;
                }
                bTheTaskIDIs181 = true;
            }
            else
            {
                return CreateFirstSubTask(ped);
            }
        }
        else
        {
            if (ped->bInVehicle)
            {
                auto pTaskSimpleCarDriveTimed = (CTaskSimpleCarDriveTimed*)CTask::operator new(112);
                if (pTaskSimpleCarDriveTimed)
                {
                    pTaskSimpleCarDriveTimed->Constructor(ped->m_pVehicle, 2000);
                    return (CTask*)pTaskSimpleCarDriveTimed;
                }
                return nullptr;
            }
            return CreateFirstSubTask(ped);
        }
    }
    if (!bTheTaskIDIs181)
    {
        if (taskId == TASK_SIMPLE_SCRATCH_HEAD)
        {
            m_nDir++;
            UpdatePathNodes(ped, m_nDir, &m_LastNode, &m_NextNode, (int8_t*)& m_nDir);

            if (m_NextNode.m_wAreaId != -1 && m_LastNode.m_wAreaId != -1)
            {
                if (m_NextNode.m_wAreaId != m_LastNode.m_wAreaId || m_NextNode.m_wNodeId != m_LastNode.m_wNodeId)
                {
                    return CreateSubTask(ped, TASK_SIMPLE_GO_TO_POINT);
                }
            }

            auto pTaskSimpleScratchHead = (CTaskSimpleScratchHead*)CTask::operator new(32);
            if (!pTaskSimpleScratchHead)
            {
                return nullptr;
            }
            pTaskSimpleScratchHead->Constructor();
            return (CTask*)pTaskSimpleScratchHead;
        }

        int theTaskID = taskId - TASK_COMPLEX_OBSERVE_TRAFFIC_LIGHTS_AND_ACHIEVE_HEADING;
        if (!theTaskID)
        {
            return CreateSubTask(ped, TASK_SIMPLE_GO_TO_POINT);
        }
        theTaskID = theTaskID - 2;
        if (!theTaskID)
        {
            return CreateSubTask(ped, TASK_SIMPLE_GO_TO_POINT);
        }
        if (theTaskID != 17)
        {
            return nullptr;
        }
    }
    if (m_bAllNodesBlocked)
    {
        m_bAllNodesBlocked = 0;
        auto pTaskSimpleScratchHead = (CTaskSimpleScratchHead*)CTask::operator new(32);
        if (pTaskSimpleScratchHead)
        {
            pTaskSimpleScratchHead->Constructor();
            return (CTask*)pTaskSimpleScratchHead;
        }
        return nullptr;
    }

    UpdateDir(ped);
    UpdatePathNodes(ped, m_nDir, &m_LastNode, &m_NextNode, (int8_t*)& m_nDir);

    if (m_NextNode.m_wAreaId != m_LastNode.m_wAreaId && m_NextNode.m_wNodeId != m_LastNode.m_wNodeId)
    {
        if (ValidNodes())
        {
            if (!m_bWanderSensibly)
            {
                return CreateSubTask(ped, TASK_SIMPLE_GO_TO_POINT);
            }

            if (ThePaths.TestForPedTrafficLight(m_LastNode, m_NextNode))
            {
                return CreateSubTask(ped, TASK_COMPLEX_OBSERVE_TRAFFIC_LIGHTS_AND_ACHIEVE_HEADING);
            }

            if (!m_bWanderSensibly || !ThePaths.TestCrossesRoad(m_LastNode, m_NextNode))
            {
                return CreateSubTask(ped, TASK_SIMPLE_GO_TO_POINT);
            }

            auto pTaskCrossRoadAndHeading = (CTaskComplexCrossRoadLookAndAchieveHeading*)CTask::operator new(20);
            if (pTaskCrossRoadAndHeading)
            {
                float fTargetHeading = ComputeTargetHeading(ped);
                pTaskCrossRoadAndHeading->Constructor(2000, fTargetHeading);
                return (CTask*)pTaskCrossRoadAndHeading;
            }
        }
        else
        {
            auto pTaskSimpleScratchHead = (CTaskSimpleScratchHead*)CTask::operator new(32);
            if (pTaskSimpleScratchHead)
            {
                pTaskSimpleScratchHead->Constructor();
                return (CTask*)pTaskSimpleScratchHead;
            }
        }
        return nullptr;
    }

    auto pTaskComplexSequence = (CTaskComplexSequence*)CTask::operator new(64);
    if (pTaskComplexSequence)
    {
        pTaskComplexSequence->Constructor();
    }

    auto pTaskSimpleStandStill = (CTaskSimpleStandStill*)CTask::operator new(32);
    if (pTaskSimpleStandStill)
    {
        pTaskSimpleStandStill->Constructor(500, 0, 0, 8.0f);
    }
    pTaskComplexSequence->AddTask(pTaskSimpleStandStill);

    auto pTaskSimpleRunAnim = (CTaskSimpleRunAnim*)CTask::operator new(32);
    if (pTaskSimpleRunAnim)
    {
        pTaskSimpleRunAnim->Constructor(ped->m_nAnimGroup, 4, 4.0f, 0);
    }
    pTaskComplexSequence->AddTask(pTaskSimpleRunAnim);

    auto pTaskSimpleScratchHead = (CTaskSimpleScratchHead*)CTask::operator new(32);
    if (pTaskSimpleScratchHead)
    {
        pTaskSimpleScratchHead->Constructor();
    }
    pTaskComplexSequence->AddTask(pTaskSimpleScratchHead);

    CVector outTargetPos;
    ComputeTargetPos(ped, &outTargetPos, &m_NextNode);
    auto pTaskSimpleGoToPoint = (CTaskSimpleGoToPoint*)CTask::operator new(48);
    if (pTaskSimpleGoToPoint)
    {
        pTaskSimpleGoToPoint->Constructor(m_nMoveState, &outTargetPos, m_fTargetRadius, 0, 0);
    }
    pTaskComplexSequence->AddTask(pTaskSimpleGoToPoint);
    return pTaskComplexSequence;
#endif
}

CTask* CTaskComplexWander::CreateFirstSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x6740E0, CTaskComplexWander*, CPed*>(this, ped);
#else
    if (ped->bInVehicle)
    {
        return CreateSubTask(ped, TASK_COMPLEX_LEAVE_CAR);
    }

    UpdateDir(ped);
    UpdatePathNodes(ped, m_nDir, &m_LastNode, &m_NextNode, (int8_t*)& m_nDir);
    return CreateSubTask(ped, TASK_SIMPLE_GO_TO_POINT);
#endif
}

CTask* CTaskComplexWander::ControlSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x674C30, CTaskComplexWander*, CPed*>(this, ped);
#else
    int subTaskId = m_pSubTask->GetId();
    if (subTaskId == TASK_COMPLEX_LEAVE_CAR || subTaskId == TASK_SIMPLE_CAR_DRIVE_TIMED)
    {
        return m_pSubTask;
    }

    if (m_bNewDir && subTaskId == TASK_SIMPLE_GO_TO_POINT)
    {
        m_bNewDir = 0;
        m_NextNode.m_wAreaId = -1;
        m_LastNode.m_wAreaId = -1;
        return CreateFirstSubTask(ped);
    }
    else
    {
        if (m_bNewNodes && subTaskId == TASK_SIMPLE_GO_TO_POINT)
        {
            m_bNewNodes = 0;
            CVector outTargetPos;
            ComputeTargetPos(ped, &outTargetPos, &m_NextNode);
            auto pTaskSimpleGoToPoint = (CTaskSimpleGoToPoint*)m_pSubTask;
            pTaskSimpleGoToPoint->UpdatePoint(&outTargetPos, 0.5, 0);
        }
        else
        {
            ScanForBlockedNodes(ped);
            ScanForStuff(ped);
        }

        if (subTaskId == TASK_SIMPLE_GO_TO_POINT)
        {
            auto pTaskSimpleGoToPoint = (CTaskSimpleGoToPoint*)m_pSubTask;
            pTaskSimpleGoToPoint->m_moveState = m_nMoveState;
            if (m_nMoveState <= PEDMOVE_WALK)
            {
                ped->Say(45, 0, 0.1, 0, 0, 0);
            }
        }

        if (ped->m_pIntelligence->m_AnotherStaticCounter > 30)
        {
            if (m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, 0))
            {
                return CreateSubTask(ped, TASK_SIMPLE_SCRATCH_HEAD);
            }
        }
    }
    return m_pSubTask;
#endif
}

int CTaskComplexWander::GetWanderType()
{
    return ((int(__thiscall*)(CTaskComplex*))plugin::GetVMT(this, 11))(this);
}

void CTaskComplexWander::ScanForStuff(CPed* ped)
{
    return ((void(__thiscall*)(CTaskComplex*, CPed*))plugin::GetVMT(this, 12))(this, ped);
}

void CTaskComplexWander::UpdateDir(CPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return ((void(__thiscall*)(CTaskComplex*, CPed*))plugin::GetVMT(this, 13))(this, pPed);
#else
    unsigned char newDir = m_nDir;
    if (m_NextNode.m_wAreaId != -1)
    {
        if (ThePaths.m_pPathNodes[m_NextNode.m_wAreaId])
        {
            CPathNode* pPathNodes = ThePaths.m_pPathNodes[m_NextNode.m_wAreaId];
            CPathNode* pPathNode = &pPathNodes[m_NextNode.m_wNodeId];
            if (pPathNode)
            {
                if (pPathNode->m_nNumLinks >= 3 && CTimer::m_FrameCounter != m_nLastUpdateDirFrameCount && m_bWanderSensibly)
                {
                    m_nLastUpdateDirFrameCount = CTimer::m_FrameCounter;
                    unsigned char remainder = (3 * CTimer::m_FrameCounter + pPed->m_nRandomSeed) % 100;
                    if (remainder <= 90u)
                    {
                        if (remainder > 80u)
                        {
                            newDir = (newDir + 10) % 8;
                        }
                    }
                    else
                    {
                        newDir = (m_nDir + 6) % 8;
                    }
                }
            }
        }
    }

    if (newDir != m_nDir)
    {
        int8_t outDir;
        UpdatePathNodes(pPed, newDir, &m_LastNode, &m_NextNode, &outDir);

        unsigned char currentDir = m_nDir;
        unsigned char theDir = outDir;
        if (outDir <= currentDir)
        {
            theDir = m_nDir;
        }

        if (theDir == currentDir)
        {
            currentDir = outDir;
        }

        if (((theDir - currentDir + 8) % 8) <= 3u)
        {
            m_nDir = newDir;
        }
    }
#endif
}

void CTaskComplexWander::UpdatePathNodes(CPed* pPed, int8_t dir, CNodeAddress* originNode, CNodeAddress* targetNode, int8_t* outDir)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((void(__thiscall*)(CTaskComplex*, CPed*, int8_t, CNodeAddress*, CNodeAddress*, int8_t*))plugin::GetVMT(this, 14))
        (this, pPed, dir, originNode, targetNode, outDir);
#else
    *originNode = *targetNode;
    targetNode->m_wAreaId = -1;

    CVector* pPedPos = &pPed->m_placement.m_vPosn;
    CMatrixLink* pPedMatrix = pPed->m_matrix;
    if (pPedMatrix)
    {
        pPedPos = &pPedMatrix->pos;
    }

    ThePaths.FindNextNodeWandering(PATH_TYPE_BOATS, pPedPos->x, pPedPos->y, pPedPos->z, originNode, targetNode, dir, outDir);
#endif
}

CTask* CTaskComplexWander::CreateSubTask(CPed* ped, int taskId)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTask*, 0x671CB0, CTaskComplexWander*, CPed*, int>(this, ped, taskId);
#else
    if (taskId > TASK_COMPLEX_LEAVE_CAR)
    {
        switch (taskId)
        {
        case TASK_SIMPLE_CAR_DRIVE_TIMED:
        {
            auto pTaskSimpleCarDriveTimed = (CTaskSimpleCarDriveTimed*)CTask::operator new(112);
            if (pTaskSimpleCarDriveTimed)
            {
                pTaskSimpleCarDriveTimed->Constructor(ped->m_pVehicle, 2000);
                return (CTask*)pTaskSimpleCarDriveTimed;
            }
            break;
        }
        case TASK_SIMPLE_GO_TO_POINT:
        {
            CVector outTargetPos;
            ComputeTargetPos(ped, &outTargetPos, &m_NextNode);
            auto pTaskGotoPoint = (CTaskSimpleGoToPoint*)CTask::operator new(48);
            if (pTaskGotoPoint)
            {
                pTaskGotoPoint->Constructor(m_nMoveState, &outTargetPos, m_fTargetRadius, 0, 0);
                return (CTask*)pTaskGotoPoint;
            }
            break;
        }
        case TASK_FINISHED:
        {
            break;
        }
        default:
        {
            return nullptr;
        }
        }
    }
    else
    {
        switch (taskId)
        {
        case TASK_COMPLEX_LEAVE_CAR:
        {
            auto pTaskComplexLeaveCar = (CTaskComplexLeaveCar*)CTask::operator new(52);
            if (pTaskComplexLeaveCar)
            {
                pTaskComplexLeaveCar->Constructor(ped->m_pVehicle, 0, 0, 1, 0);
                return pTaskComplexLeaveCar;
            }
            break;
        }
        case TASK_COMPLEX_OBSERVE_TRAFFIC_LIGHTS_AND_ACHIEVE_HEADING:
        {
            auto pTaskTrafficLightAndAchieveHeading = (CTaskComplexObserveTrafficLightsAndAchieveHeading*)CTask::operator new(20);
            if (pTaskTrafficLightAndAchieveHeading)
            {
                float fTargetHeading = ComputeTargetHeading(ped);
                pTaskTrafficLightAndAchieveHeading->Constructor(2000, fTargetHeading);
                return pTaskTrafficLightAndAchieveHeading;
            }
            break;
        }
        case TASK_COMPLEX_CROSS_ROAD_LOOK_AND_ACHIEVE_HEADING:
        {
            auto pTaskCrossRoadAndAchieveHeading = (CTaskComplexCrossRoadLookAndAchieveHeading*)CTask::operator new(20);
            if (pTaskCrossRoadAndAchieveHeading)
            {
                float fTargetHeading = ComputeTargetHeading(ped);
                pTaskCrossRoadAndAchieveHeading->Constructor(2000, fTargetHeading);;
                return pTaskCrossRoadAndAchieveHeading;
            }
            break;
        }
        case TASK_SIMPLE_SCRATCH_HEAD:
        {
            auto pTaskSimpleScratchHead = (CTaskSimpleScratchHead*)CTask::operator new(32);
            if (pTaskSimpleScratchHead)
            {
                pTaskSimpleScratchHead->Constructor();
                return pTaskSimpleScratchHead;
            }
            break;
        }
        default:
        {
            return nullptr;
        }
        }
    }
    return nullptr;
#endif
}

float CTaskComplexWander::ComputeTargetHeading(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<float, 0x66F530, CTaskComplexWander*, CPed*>(this, ped);
#else
    CVector outPosition;
    ThePaths.TakeWidthIntoAccountForWandering(&outPosition, m_NextNode, ped->m_nRandomSeed);

    CVector* pPedPos = &ped->m_placement.m_vPosn;
    CMatrixLink* pPedMatrix = ped->m_matrix;
    if (pPedMatrix)
    {
        pPedPos = &pPedMatrix->pos;
    }

    outPosition.x -= pPedPos->x;
    outPosition.y -= pPedPos->y;
    float radianAngle = CGeneral::GetRadianAngleBetweenPoints(outPosition.x, outPosition.y, 0.0f, 0.0f);
    return CGeneral::LimitRadianAngle(radianAngle);
#endif
}

void CTaskComplexWander::ComputeTargetPos(CPed* pPed, CVector* pOutTargetPos, CNodeAddress* pTargetNodeAddress)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x669F60, CTaskComplexWander*, CPed*, CVector*, CNodeAddress*>(this, pPed, pOutTargetPos, pTargetNodeAddress);
#else
    CVector outTargetPos;
    CVector* pTargetPos = ThePaths.TakeWidthIntoAccountForWandering(&outTargetPos, *pTargetNodeAddress, pPed->m_nRandomSeed);
    pOutTargetPos->x = pTargetPos->x;
    pOutTargetPos->y = pTargetPos->y;
    pOutTargetPos->z = pTargetPos->z;
    pOutTargetPos->z = pOutTargetPos->z + 1.0;
#endif
}

bool CTaskComplexWander::ValidNodes()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x669F30, CTaskComplexWander*>(this);
#else
    if (m_NextNode.m_wAreaId != -1 && m_LastNode.m_wAreaId != -1)
    {
        if (m_NextNode.m_wAreaId != m_LastNode.m_wAreaId || m_NextNode.m_wNodeId != m_LastNode.m_wNodeId)
        {
            return true;
        }
    }
    return false;
#endif
}

void CTaskComplexWander::ScanForBlockedNodes(CPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x674560, CTaskComplexWander*, CPed*>(this, pPed);
#else
    if (m_pSubTask->GetId() == TASK_SIMPLE_GO_TO_POINT && m_NextNode.m_wAreaId != -1)
    {
        if (ScanForBlockedNode(pPed, &m_NextNode))
        {
            m_pSubTask->MakeAbortable(pPed, ABORT_PRIORITY_LEISURE, 0);

            int8_t outDir = 0;
            UpdatePathNodes(pPed, m_nDir, &m_LastNode, &m_NextNode, &outDir);
            if (ScanForBlockedNode(pPed, &m_NextNode) || m_NextNode.operatorEqual(&m_LastNode))
            {
                m_bAllNodesBlocked = 1;
            }
        }
    }
#endif
}

bool CTaskComplexWander::ScanForBlockedNode(CPed* pPed, CNodeAddress* targetNodeAddress)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x671EF0, CTaskComplexWander*, CPed*, CNodeAddress*>(this, pPed, targetNodeAddress);
#else
    CVector outVec;
    CVector* pNewNodePos = ThePaths.TakeWidthIntoAccountForWandering(&outVec, *targetNodeAddress, pPed->m_nRandomSeed);

    CMatrixLink* pPedMatrix = pPed->m_matrix;
    CVector* pPedPos = &pPed->m_placement.m_vPosn;
    if (pPedMatrix)
    {
        pPedPos = &pPedMatrix->pos;
    }

    float fX = pNewNodePos->x - pPedPos->x;
    float fY = pNewNodePos->y - pPedPos->y;
    if (3.0f * 3.0f >= fY * fY + fX * fX)
    {
        CPed* pClosestPed = (CPed*)pPed->m_pIntelligence->m_entityScanner.m_pClosestEntityInRange;
        if (ScanForBlockedNode(pNewNodePos, pClosestPed))
        {
            return true;
        }

        CVehicle* pClosestVehicle = (CVehicle*)pPed->m_pIntelligence->m_vehicleScanner.m_pClosestEntityInRange;
        if (ScanForBlockedNode(pNewNodePos, pClosestVehicle))
        {
            return true;
        }
    }
    return false;
#endif
}

bool CTaskComplexWander::ScanForBlockedNode(CVector* position, CEntity* pEntity)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x66F4C0, CTaskComplexWander*, CVector*, CEntity*>(this, position, pEntity);
#else
    if (!pEntity)
    {
        return false;
    }

    CVector* pEntityPos = &pEntity->m_placement.m_vPosn;
    CMatrixLink* pEntityMatrix = pEntity->m_matrix;
    if (pEntityMatrix)
    {
        pEntityPos = &pEntityMatrix->pos;
    }

    float fX = position->x - pEntityPos->x;
    float fY = position->y - pEntityPos->y;
    float fRadius = CModelInfo::ms_modelInfoPtrs[pEntity->m_nModelIndex]->m_pColModel->m_boundSphere.m_fRadius + 1.0f;

    if (fRadius * fRadius > (fX * fX + fY * fY))
    {
        return true;
    }
    return false;
#endif
}
