#include "StdInc.h"

void CTaskComplexWander::InjectHooks()
{
    HookInstall(0x66F450, &CTaskComplexWander::Constructor, 7);
    HookInstall(0x460CD0, &CTaskComplexWander::GetId_Reversed, 7);
    HookInstall(0x674140, &CTaskComplexWander::CreateNextSubTask_Reversed, 7);
    HookInstall(0x6740E0, &CTaskComplexWander::CreateFirstSubTask_Reversed, 7);
    HookInstall(0x674C30, &CTaskComplexWander::ControlSubTask_Reversed, 7);
    HookInstall(0x669DA0, &CTaskComplexWander::UpdateDir_Reversed, 7);
    HookInstall(0x669ED0, &CTaskComplexWander::UpdatePathNodes_Reversed, 7);
    HookInstall(0x671CB0, &CTaskComplexWander::CreateSubTask, 7);
    HookInstall(0x669F60, &CTaskComplexWander::ComputeTargetPos, 7);
    HookInstall(0x66F530, &CTaskComplexWander::ComputeTargetHeading, 7);
    HookInstall(0x669F30, &CTaskComplexWander::ValidNodes, 7);
    HookInstall(0x674560, &CTaskComplexWander::ScanForBlockedNodes, 7);
    HookInstall(0x671EF0, (bool(CTaskComplexWander::*)(CPed*, CNodeAddress*))&CTaskComplexWander::ScanForBlockedNode, 7);
    HookInstall(0x66F4C0, (bool(CTaskComplexWander::*)(CVector*, CEntity*))&CTaskComplexWander::ScanForBlockedNode, 7);
    HookInstall(0x673D00, CTaskComplexWander::GetWanderTaskByPedType, 7);
}

CTaskComplexWander::CTaskComplexWander(int moveState, unsigned char dir, bool bWanderSensibly, float fTargetRadius) {
    m_nMoveState = moveState;
    m_nDir = dir;
    m_fTargetRadius = fTargetRadius;
    m_LastNode.m_wAreaId = -1;
    m_NextNode.m_wAreaId = -1;
    m_nFlags = 0xF0;
    m_bWanderSensibly = bWanderSensibly;
    m_nLastUpdateDirFrameCount = 0;
}

CTaskComplexWander::~CTaskComplexWander() {
    // nothing here
}

CTaskComplexWander* CTaskComplexWander::Constructor(int moveState, unsigned char dir, bool bWanderSensibly, float fTargetRadius) {
    this->CTaskComplexWander::CTaskComplexWander(moveState, dir, bWanderSensibly, 0.5f);
    return this;
}

eTaskType CTaskComplexWander::GetId()
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return ((eTaskType(__thiscall*)(CTask*))0x460CD0)(this);
#else
    return GetId_Reversed();
#endif
}

CTask* CTaskComplexWander::CreateNextSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x674140, CTaskComplexWander*, CPed*>(this, ped);
#else
    return CreateNextSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexWander::CreateFirstSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x6740E0, CTaskComplexWander*, CPed*>(this, ped);
#else
    return CreateFirstSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexWander::ControlSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x674C30, CTaskComplexWander*, CPed*>(this, ped);
#else
    return ControlSubTask_Reversed(ped);
#endif
}

void CTaskComplexWander::UpdateDir(CPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return ((void(__thiscall*)(CTaskComplex*, CPed*))0x669DA0)(this, pPed);
#else
    return UpdateDir_Reversed(pPed);
#endif
}

void CTaskComplexWander::UpdatePathNodes(CPed* pPed, int8_t dir, CNodeAddress* originNode, CNodeAddress* targetNode, int8_t* outDir)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((void(__thiscall*)(CTaskComplex*, CPed*, int8_t, CNodeAddress*, CNodeAddress*, int8_t*))0x669ED0)
        (this, pPed, dir, originNode, targetNode, outDir);
#else
    return UpdatePathNodes_Reversed(pPed, dir, originNode, targetNode, outDir);
#endif
}

CTask* CTaskComplexWander::CreateNextSubTask_Reversed(CPed* ped)
{
    bool bTheTaskIDIs181 = false;
    int taskId = m_pSubTask->GetId();
    if (taskId > TASK_SIMPLE_SCRATCH_HEAD)
    {
        int theTaskID = taskId - TASK_COMPLEX_LEAVE_CAR;
        if (theTaskID) // if taskId >= TASK_COMPLEX_LEAVE_CAR_AND_DIE
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

    CTaskComplexSequence* pTaskComplexSequence = new CTaskComplexSequence();
    auto pTaskSimpleStandStill = new CTaskSimpleStandStill(500, 0, 0, 8.0f);
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
    auto pTaskSimpleGoToPoint = new CTaskSimpleGoToPoint(m_nMoveState, outTargetPos, m_fTargetRadius, false, false);
    pTaskComplexSequence->AddTask(pTaskSimpleGoToPoint);
    return pTaskComplexSequence;
}

CTask* CTaskComplexWander::CreateFirstSubTask_Reversed(CPed* ped)
{
    if (ped->bInVehicle)
    {
        return CreateSubTask(ped, TASK_COMPLEX_LEAVE_CAR);
    }

    UpdateDir(ped);
    UpdatePathNodes(ped, m_nDir, &m_LastNode, &m_NextNode, (int8_t*)& m_nDir);
    return CreateSubTask(ped, TASK_SIMPLE_GO_TO_POINT);
}

CTask* CTaskComplexWander::ControlSubTask_Reversed(CPed* ped)
{
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
            pTaskSimpleGoToPoint->UpdatePoint(outTargetPos, 0.5, 0);
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
                ped->Say(45, 0, 0.1f, 0, 0, 0);
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
}

void CTaskComplexWander::UpdateDir_Reversed(CPed* pPed)
{
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
}

void CTaskComplexWander::UpdatePathNodes_Reversed(CPed* pPed, int8_t dir, CNodeAddress* originNode, CNodeAddress* targetNode, int8_t* outDir)
{
    *originNode = *targetNode;
    targetNode->m_wAreaId = -1;
    const CVector& pos = pPed->GetPosition();
    ThePaths.FindNextNodeWandering(PATH_TYPE_BOATS, pos.x, pos.y, pos.z, originNode, targetNode, dir, outDir);
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
            auto pTaskGotoPoint = new CTaskSimpleGoToPoint(m_nMoveState, outTargetPos, m_fTargetRadius, false, false);
            if (pTaskGotoPoint)
                return (CTask*)pTaskGotoPoint;
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
    CVector position;
    ThePaths.TakeWidthIntoAccountForWandering(&position, m_NextNode, ped->m_nRandomSeed);
    position -= ped->GetPosition();
    float radianAngle = CGeneral::GetRadianAngleBetweenPoints(position.x, position.y, 0.0f, 0.0f);
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
    *pOutTargetPos = *pTargetPos;
    pOutTargetPos->z += 1.0f;
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
    CVector2D distance = *pNewNodePos - pPed->GetPosition();
    if (3.0f * 3.0f >= distance.SquaredMagnitude()) {
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
        return false;
    CVector2D distance = *position - pEntity->GetPosition();
    float fRadius = CModelInfo::GetModelInfo(pEntity->m_nModelIndex)->GetColModel()->GetBoundRadius() + 1.0f;
    if (fRadius * fRadius > distance.SquaredMagnitude())
        return true;
    return false;
#endif
}

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
    default:
    {
        auto pTaskComplexWanderStandard = (CTaskComplexWanderStandard*)CTask::operator new(0x38);
        if (pTaskComplexWanderStandard)
        {
            pTaskComplexWanderStandard->Constructor(PEDMOVE_WALK, randomDir, 1);
            return pTaskComplexWanderStandard;
        }
        break;
    }
    }
    return nullptr;
#endif
}
