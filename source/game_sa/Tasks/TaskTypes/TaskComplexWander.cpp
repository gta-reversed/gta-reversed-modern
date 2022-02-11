#include "StdInc.h"

#include "TaskComplexWander.h"

#include "TaskSimpleCarDriveTimed.h"
#include "TaskSimpleScratchHead.h"
#include "TaskSimpleStandStill.h"
#include "TaskSimpleGoToPoint.h"
#include "TaskSimpleRunAnim.h"

#include "TaskComplexObserveTrafficLightsAndAchieveHeading.h"
#include "TaskComplexCrossRoadLookAndAchieveHeading.h"
#include "TaskComplexWanderProstitute.h"
#include "TaskComplexWanderStandard.h"
#include "TaskComplexWanderCriminal.h"
#include "TaskComplexWanderMedic.h"
#include "TaskComplexWanderCop.h"
#include "TaskComplexLeaveCar.h"

void CTaskComplexWander::InjectHooks()
{
    RH_ScopedClass(CTaskComplexWander);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x66F450);
    RH_ScopedInstall(GetId_Reversed, 0x460CD0);
    RH_ScopedInstall(CreateNextSubTask_Reversed, 0x674140);
    RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x6740E0);
    RH_ScopedInstall(ControlSubTask_Reversed, 0x674C30);
    RH_ScopedInstall(UpdateDir_Reversed, 0x669DA0);
    RH_ScopedInstall(UpdatePathNodes_Reversed, 0x669ED0);
    RH_ScopedInstall(CreateSubTask, 0x671CB0);
    RH_ScopedInstall(ComputeTargetPos, 0x669F60);
    RH_ScopedInstall(ComputeTargetHeading, 0x66F530);
    RH_ScopedInstall(ValidNodes, 0x669F30);
    RH_ScopedInstall(ScanForBlockedNodes, 0x674560);
    RH_ScopedOverloadedInstall(ScanForBlockedNode, "", 0x671EF0, bool(CTaskComplexWander::*)(CPed*, CNodeAddress*));
    RH_ScopedOverloadedInstall(ScanForBlockedNode, "1", 0x66F4C0, bool(CTaskComplexWander::*)(CVector*, CEntity*));
    RH_ScopedInstall(GetWanderTaskByPedType, 0x673D00);
}

CTaskComplexWander::CTaskComplexWander(int32 moveState, uint8 dir, bool bWanderSensibly, float fTargetRadius) {
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

CTaskComplexWander* CTaskComplexWander::Constructor(int32 moveState, uint8 dir, bool bWanderSensibly, float fTargetRadius) {
    this->CTaskComplexWander::CTaskComplexWander(moveState, dir, bWanderSensibly, 0.5f);
    return this;
}

// 0x460CD0
eTaskType CTaskComplexWander::GetTaskType()
{
    return GetId_Reversed();
}

// 0x674140
CTask* CTaskComplexWander::CreateNextSubTask(CPed* ped)
{
    return CreateNextSubTask_Reversed(ped);
}

// 0x6740E0
CTask* CTaskComplexWander::CreateFirstSubTask(CPed* ped)
{
    return CreateFirstSubTask_Reversed(ped);
}

// 0x674C30
CTask* CTaskComplexWander::ControlSubTask(CPed* ped)
{
    return ControlSubTask_Reversed(ped);
}

// 0x669DA0
void CTaskComplexWander::UpdateDir(CPed* ped)
{
    return UpdateDir_Reversed(ped);
}

// 0x669ED0
void CTaskComplexWander::UpdatePathNodes(CPed* ped, int8 dir, CNodeAddress* originNode, CNodeAddress* targetNode, int8* outDir)
{
    return UpdatePathNodes_Reversed(ped, dir, originNode, targetNode, outDir);
}

CTask* CTaskComplexWander::CreateNextSubTask_Reversed(CPed* ped)
{
    bool bTheTaskIDIs181 = false;
    int32 taskId = m_pSubTask->GetTaskType();
    if (taskId > TASK_SIMPLE_SCRATCH_HEAD)
    {
        int32 theTaskID = taskId - TASK_COMPLEX_LEAVE_CAR;
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
                return new CTaskSimpleCarDriveTimed(ped->m_pVehicle, 2000);
            }
            return CreateFirstSubTask(ped);
        }
    }
    if (!bTheTaskIDIs181)
    {
        if (taskId == TASK_SIMPLE_SCRATCH_HEAD)
        {
            m_nDir++;
            UpdatePathNodes(ped, m_nDir, &m_LastNode, &m_NextNode, (int8*)& m_nDir);

            if (m_NextNode.m_wAreaId != (uint16)-1 && m_LastNode.m_wAreaId != (uint16)-1)
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

        int32 theTaskID = taskId - TASK_COMPLEX_OBSERVE_TRAFFIC_LIGHTS_AND_ACHIEVE_HEADING;
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
    UpdatePathNodes(ped, m_nDir, &m_LastNode, &m_NextNode, (int8*)& m_nDir);

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

            float fTargetHeading = ComputeTargetHeading(ped);
            return new CTaskComplexCrossRoadLookAndAchieveHeading(2000, fTargetHeading);
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

    auto* sequence = new CTaskComplexSequence();
    auto pTaskSimpleStandStill = new CTaskSimpleStandStill(500, false, false, 8.0f);
    sequence->AddTask(pTaskSimpleStandStill);

    sequence->AddTask(new CTaskSimpleRunAnim(ped->m_nAnimGroup, ANIM_ID_ROADCROSS, 4.0F, false));

    auto pTaskSimpleScratchHead = (CTaskSimpleScratchHead*)CTask::operator new(32);
    if (pTaskSimpleScratchHead)
    {
        pTaskSimpleScratchHead->Constructor();
    }
    sequence->AddTask(pTaskSimpleScratchHead);

    CVector outTargetPos;
    ComputeTargetPos(ped, &outTargetPos, &m_NextNode);
    auto pTaskSimpleGoToPoint = new CTaskSimpleGoToPoint(m_nMoveState, outTargetPos, m_fTargetRadius, false, false);
    sequence->AddTask(pTaskSimpleGoToPoint);
    return sequence;
}

CTask* CTaskComplexWander::CreateFirstSubTask_Reversed(CPed* ped)
{
    if (ped->bInVehicle)
    {
        return CreateSubTask(ped, TASK_COMPLEX_LEAVE_CAR);
    }

    UpdateDir(ped);
    UpdatePathNodes(ped, m_nDir, &m_LastNode, &m_NextNode, (int8*)& m_nDir);
    return CreateSubTask(ped, TASK_SIMPLE_GO_TO_POINT);
}

CTask* CTaskComplexWander::ControlSubTask_Reversed(CPed* ped)
{
    int32 subTaskId = m_pSubTask->GetTaskType();
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
            pTaskSimpleGoToPoint->UpdatePoint(outTargetPos, 0.5, false);
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
            if (m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr))
            {
                return CreateSubTask(ped, TASK_SIMPLE_SCRATCH_HEAD);
            }
        }
    }
    return m_pSubTask;
}

void CTaskComplexWander::UpdateDir_Reversed(CPed* ped)
{
    uint8 newDir = m_nDir;
    if (m_NextNode.m_wAreaId != (uint16)-1)
    {
        if (ThePaths.m_pPathNodes[m_NextNode.m_wAreaId])
        {
            CPathNode* pathNodes = ThePaths.m_pPathNodes[m_NextNode.m_wAreaId];
            CPathNode* pathNode = &pathNodes[m_NextNode.m_wNodeId];
            if (pathNode)
            {
                if (pathNode->m_nNumLinks >= 3 && CTimer::GetFrameCounter() != m_nLastUpdateDirFrameCount && m_bWanderSensibly)
                {
                    m_nLastUpdateDirFrameCount = CTimer::GetFrameCounter();
                    uint8 remainder = (3 * CTimer::GetFrameCounter() + ped->m_nRandomSeed) % 100;
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
        int8 outDir;
        UpdatePathNodes(ped, newDir, &m_LastNode, &m_NextNode, &outDir);

        uint8 currentDir = m_nDir;
        uint8 theDir = outDir;
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

void CTaskComplexWander::UpdatePathNodes_Reversed(CPed* ped, int8 dir, CNodeAddress* originNode, CNodeAddress* targetNode, int8* outDir)
{
    *originNode = *targetNode;
    targetNode->m_wAreaId = -1;
    const CVector& pos = ped->GetPosition();
    ThePaths.FindNextNodeWandering(PATH_TYPE_BOATS, pos.x, pos.y, pos.z, originNode, targetNode, dir, outDir);
}

// 0x671CB0
CTask* CTaskComplexWander::CreateSubTask(CPed* ped, int32 taskId)
{
    if (taskId > TASK_COMPLEX_LEAVE_CAR)
    {
        switch (taskId)
        {
        case TASK_SIMPLE_CAR_DRIVE_TIMED:
        {
            return new CTaskSimpleCarDriveTimed(ped->m_pVehicle, 2000);
            break;
        }
        case TASK_SIMPLE_GO_TO_POINT:
        {
            CVector outTargetPos;
            ComputeTargetPos(ped, &outTargetPos, &m_NextNode);
            return new CTaskSimpleGoToPoint(m_nMoveState, outTargetPos, m_fTargetRadius, false, false);
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
            return new CTaskComplexLeaveCar(ped->m_pVehicle, 0, 0, true, false);
        }
        case TASK_COMPLEX_OBSERVE_TRAFFIC_LIGHTS_AND_ACHIEVE_HEADING:
        {
            return new CTaskComplexObserveTrafficLightsAndAchieveHeading(2000, ComputeTargetHeading(ped));
        }
        case TASK_COMPLEX_CROSS_ROAD_LOOK_AND_ACHIEVE_HEADING:
        {
            return new CTaskComplexCrossRoadLookAndAchieveHeading(2000, ComputeTargetHeading(ped));
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
}

// 0x66F530
float CTaskComplexWander::ComputeTargetHeading(CPed* ped)
{
    CVector position;
    ThePaths.TakeWidthIntoAccountForWandering(&position, m_NextNode, ped->m_nRandomSeed);
    position -= ped->GetPosition();
    float radianAngle = CGeneral::GetRadianAngleBetweenPoints(position.x, position.y, 0.0f, 0.0f);
    return CGeneral::LimitRadianAngle(radianAngle);
}

// 0x669F60
void CTaskComplexWander::ComputeTargetPos(CPed* ped, CVector* pOutTargetPos, CNodeAddress* pTargetNodeAddress)
{
    CVector outTargetPos;
    CVector* pTargetPos = ThePaths.TakeWidthIntoAccountForWandering(&outTargetPos, *pTargetNodeAddress, ped->m_nRandomSeed);
    *pOutTargetPos = *pTargetPos;
    pOutTargetPos->z += 1.0f;
}

// 0x669F30
bool CTaskComplexWander::ValidNodes()
{
    if (m_NextNode.m_wAreaId != (uint16)-1 && m_LastNode.m_wAreaId != (uint16)-1)
    {
        if (m_NextNode.m_wAreaId != m_LastNode.m_wAreaId || m_NextNode.m_wNodeId != m_LastNode.m_wNodeId)
        {
            return true;
        }
    }
    return false;
}

// 0x674560
void CTaskComplexWander::ScanForBlockedNodes(CPed* ped)
{
    if (m_pSubTask->GetTaskType() == TASK_SIMPLE_GO_TO_POINT && m_NextNode.m_wAreaId != (uint16)-1)
    {
        if (ScanForBlockedNode(ped, &m_NextNode))
        {
            m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_LEISURE, nullptr);

            int8 outDir = 0;
            UpdatePathNodes(ped, m_nDir, &m_LastNode, &m_NextNode, &outDir);
            if (ScanForBlockedNode(ped, &m_NextNode) || &m_NextNode == &m_LastNode)
            {
                m_bAllNodesBlocked = 1;
            }
        }
    }
}

// 0x671EF0
bool CTaskComplexWander::ScanForBlockedNode(CPed* ped, CNodeAddress* targetNodeAddress)
{
    CVector outVec;
    CVector* pNewNodePos = ThePaths.TakeWidthIntoAccountForWandering(&outVec, *targetNodeAddress, ped->m_nRandomSeed);
    CVector2D distance = *pNewNodePos - ped->GetPosition();
    if (3.0f * 3.0f >= distance.SquaredMagnitude()) {
        CPed* closestPed = ped->m_pIntelligence->m_entityScanner.m_pClosestEntityInRange->AsPed();
        if (ScanForBlockedNode(pNewNodePos, closestPed))
        {
            return true;
        }

        CVehicle* closestVehicle = ped->GetIntelligence()->m_vehicleScanner.m_pClosestEntityInRange->AsVehicle();
        if (ScanForBlockedNode(pNewNodePos, closestVehicle))
        {
            return true;
        }
    }
    return false;
}

// 0x66F4C0
bool CTaskComplexWander::ScanForBlockedNode(CVector* position, CEntity* entity)
{
    if (!entity)
        return false;

    CVector2D distance = *position - entity->GetPosition();
    float fRadius = CModelInfo::GetModelInfo(entity->m_nModelIndex)->GetColModel()->GetBoundRadius() + 1.0f;
    if (fRadius * fRadius > distance.SquaredMagnitude())
        return true;

    return false;
}

// 0x673D00
CTaskComplexWander* CTaskComplexWander::GetWanderTaskByPedType(CPed* ped)
{
    uint8 randomDir = CGeneral::GetRandomNumberInRange(0, 8);
    switch (ped->m_nPedType)
    {
    case PED_TYPE_COP:
    {
        return new CTaskComplexWanderCop(PEDMOVE_WALK, randomDir);
    }
    case PED_TYPE_MEDIC:
    {
        auto pTaskComplexWanderMedic = (CTaskComplexWanderMedic*)CTask::operator new(40);
        if (pTaskComplexWanderMedic)
        {
            pTaskComplexWanderMedic->Constructor(PEDMOVE_WALK, randomDir, true);
            return pTaskComplexWanderMedic;
        }
        break;
    }
    case PED_TYPE_CRIMINAL:
    {
        auto pTaskComplexWanderCriminal = (CTaskComplexWanderCriminal*)CTask::operator new(56);
        if (pTaskComplexWanderCriminal)
        {
            pTaskComplexWanderCriminal->Constructor(PEDMOVE_WALK, randomDir, true);
            return pTaskComplexWanderCriminal;
        }
        break;
    }
    case PED_TYPE_PROSTITUTE:
    {
        auto pTaskComplexWanderProstitute = (CTaskComplexWanderProstitute*)CTask::operator new(60);
        if (pTaskComplexWanderProstitute)
        {
            pTaskComplexWanderProstitute->Constructor(PEDMOVE_WALK, randomDir, true);
            return pTaskComplexWanderProstitute;
        }
        break;
    }
    default:
    {
        auto pTaskComplexWanderStandard = (CTaskComplexWanderStandard*)CTask::operator new(0x38);
        if (pTaskComplexWanderStandard)
        {
            pTaskComplexWanderStandard->Constructor(PEDMOVE_WALK, randomDir, true);
            return pTaskComplexWanderStandard;
        }
        break;
    }
    }
    return nullptr;
}
