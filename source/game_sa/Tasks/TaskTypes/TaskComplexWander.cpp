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

void CTaskComplexWander::InjectHooks() {
    RH_ScopedClass(CTaskComplexWander);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x66F450);
    RH_ScopedVirtualInstall(CreateNextSubTask, 0x674140);
    RH_ScopedVirtualInstall(CreateFirstSubTask, 0x6740E0);
    RH_ScopedVirtualInstall(ControlSubTask, 0x674C30);
    RH_ScopedVirtualInstall(UpdateDir, 0x669DA0);
    RH_ScopedVirtualInstall(UpdatePathNodes, 0x669ED0);
    RH_ScopedInstall(CreateSubTask, 0x671CB0);
    RH_ScopedInstall(ComputeTargetPos, 0x669F60);
    RH_ScopedInstall(ComputeTargetHeading, 0x66F530);
    RH_ScopedInstall(ValidNodes, 0x669F30);
    RH_ScopedInstall(ScanForBlockedNodes, 0x674560);
    RH_ScopedOverloadedInstall(ScanForBlockedNode, "", 0x671EF0, bool(CTaskComplexWander::*)(CPed*, const CNodeAddress&));
    RH_ScopedOverloadedInstall(ScanForBlockedNode, "1", 0x66F4C0, bool(CTaskComplexWander::*)(CVector*, CEntity*));
    RH_ScopedInstall(GetWanderTaskByPedType, 0x673D00);
}

CTaskComplexWander::CTaskComplexWander(int32 moveState, uint8 dir, bool bWanderSensibly, float fTargetRadius) {
    m_nMoveState = static_cast<eMoveState>(moveState); // todo: change signature
    m_nDir = dir;
    m_fTargetRadius = fTargetRadius;
    m_LastNode.m_wAreaId = (uint16)-1;
    m_NextNode.m_wAreaId = (uint16)-1;
    m_nFlags = 0xF0;
    m_bWanderSensibly = bWanderSensibly;
    m_nLastUpdateDirFrameCount = 0;
}

CTaskComplexWander* CTaskComplexWander::Constructor(int32 moveState, uint8 dir, bool bWanderSensibly, float fTargetRadius) {
    this->CTaskComplexWander::CTaskComplexWander(moveState, dir, bWanderSensibly, 0.5f);
    return this;
}

// 0x674140
CTask* CTaskComplexWander::CreateNextSubTask(CPed* ped) {
    return CreateNextSubTask_Reversed(ped);
}

// 0x6740E0
CTask* CTaskComplexWander::CreateFirstSubTask(CPed* ped) {
    return CreateFirstSubTask_Reversed(ped);
}

// 0x674C30
CTask* CTaskComplexWander::ControlSubTask(CPed* ped) {
    return ControlSubTask_Reversed(ped);
}

// 0x669DA0
void CTaskComplexWander::UpdateDir(CPed* ped) {
    return UpdateDir_Reversed(ped);
}

// 0x669ED0
void CTaskComplexWander::UpdatePathNodes(const CPed* ped, uint8 dir, CNodeAddress& originNode, CNodeAddress& targetNode, uint8& outDir) {
    return UpdatePathNodes_Reversed(ped, dir, originNode, targetNode, outDir);
}

CTask* CTaskComplexWander::CreateNextSubTask_Reversed(CPed* ped) {
    bool bTheTaskIDIs181 = false;
    int32 taskId = m_pSubTask->GetTaskType();
    if (taskId > TASK_SIMPLE_SCRATCH_HEAD) {
        int32 theTaskID = taskId - TASK_COMPLEX_LEAVE_CAR;
        if (theTaskID) // if taskId >= TASK_COMPLEX_LEAVE_CAR_AND_DIE
        {
            theTaskID = theTaskID - 15;
            if (theTaskID) {
                if (theTaskID != 181) {
                    return nullptr;
                }
                bTheTaskIDIs181 = true;
            } else {
                return CreateFirstSubTask(ped);
            }
        } else {
            if (ped->bInVehicle) {
                return new CTaskSimpleCarDriveTimed(ped->m_pVehicle, 2000);
            }
            return CreateFirstSubTask(ped);
        }
    }
    if (!bTheTaskIDIs181) {
        if (taskId == TASK_SIMPLE_SCRATCH_HEAD) {
            m_nDir++;
            UpdatePathNodes(ped, m_nDir, m_LastNode, m_NextNode, m_nDir);

            if (m_NextNode.IsAreaValid() && m_LastNode.IsAreaValid())
            {
                if (m_NextNode.m_wAreaId != m_LastNode.m_wAreaId || m_NextNode.m_wNodeId != m_LastNode.m_wNodeId)
                {
                    return CreateSubTask(ped, TASK_SIMPLE_GO_TO_POINT);
                }
            }

            return new CTaskSimpleScratchHead();
        }

        int32 theTaskID = taskId - TASK_COMPLEX_OBSERVE_TRAFFIC_LIGHTS_AND_ACHIEVE_HEADING;
        if (!theTaskID) {
            return CreateSubTask(ped, TASK_SIMPLE_GO_TO_POINT);
        }
        theTaskID = theTaskID - 2;
        if (!theTaskID) {
            return CreateSubTask(ped, TASK_SIMPLE_GO_TO_POINT);
        }
        if (theTaskID != 17) {
            return nullptr;
        }
    }
    if (m_bAllNodesBlocked) {
        m_bAllNodesBlocked = 0;
        return new CTaskSimpleScratchHead();
    }

    UpdateDir(ped);
    UpdatePathNodes(ped, m_nDir, m_LastNode, m_NextNode, m_nDir);

    if (m_NextNode.m_wAreaId != m_LastNode.m_wAreaId && m_NextNode.m_wNodeId != m_LastNode.m_wNodeId) {
        if (ValidNodes()) {
            if (!m_bWanderSensibly) {
                return CreateSubTask(ped, TASK_SIMPLE_GO_TO_POINT);
            }

            if (ThePaths.TestForPedTrafficLight(m_LastNode, m_NextNode)) {
                return CreateSubTask(ped, TASK_COMPLEX_OBSERVE_TRAFFIC_LIGHTS_AND_ACHIEVE_HEADING);
            }

            if (!m_bWanderSensibly || !ThePaths.TestCrossesRoad(m_LastNode, m_NextNode)) {
                return CreateSubTask(ped, TASK_SIMPLE_GO_TO_POINT);
            }

            float fTargetHeading = ComputeTargetHeading(ped);
            return new CTaskComplexCrossRoadLookAndAchieveHeading(2000, fTargetHeading);
        }

        return new CTaskSimpleScratchHead();
    }

    auto* sequence = new CTaskComplexSequence();

    sequence->AddTask(new CTaskSimpleStandStill(500, false, false, 8.0f));
    sequence->AddTask(new CTaskSimpleRunAnim(ped->m_nAnimGroup, ANIM_ID_ROADCROSS, 4.0F, false));
    sequence->AddTask(new CTaskSimpleScratchHead());

    CVector outTargetPos;
    ComputeTargetPos(ped, outTargetPos, m_NextNode);
    sequence->AddTask(new CTaskSimpleGoToPoint(m_nMoveState, outTargetPos, m_fTargetRadius, false, false));

    return sequence;
}

CTask* CTaskComplexWander::CreateFirstSubTask_Reversed(CPed* ped) {
    if (ped->bInVehicle) {
        return CreateSubTask(ped, TASK_COMPLEX_LEAVE_CAR);
    }

    UpdateDir(ped);
    UpdatePathNodes(ped, m_nDir, m_LastNode, m_NextNode, m_nDir);
    return CreateSubTask(ped, TASK_SIMPLE_GO_TO_POINT);
}

CTask* CTaskComplexWander::ControlSubTask_Reversed(CPed* ped) {
    auto subTaskId = m_pSubTask->GetTaskType();
    if (subTaskId == TASK_COMPLEX_LEAVE_CAR || subTaskId == TASK_SIMPLE_CAR_DRIVE_TIMED) {
        return m_pSubTask;
    }

    if (m_bNewDir && subTaskId == TASK_SIMPLE_GO_TO_POINT) {
        m_bNewDir = 0;
        m_NextNode.m_wAreaId = (uint16)-1;
        m_LastNode.m_wAreaId = (uint16)-1;
        return CreateFirstSubTask(ped);
    } else {
        if (m_bNewNodes && subTaskId == TASK_SIMPLE_GO_TO_POINT) {
            m_bNewNodes = 0;
            CVector outTargetPos;
            ComputeTargetPos(ped, outTargetPos, m_NextNode);
            static_cast<CTaskSimpleGoToPoint*>(m_pSubTask)->UpdatePoint(outTargetPos, 0.5f, false);
        } else {
            ScanForBlockedNodes(ped);
            ScanForStuff(ped);
        }

        if (subTaskId == TASK_SIMPLE_GO_TO_POINT) {
            static_cast<CTaskSimpleGoToPoint*>(m_pSubTask)->m_moveState = m_nMoveState;
            if (m_nMoveState <= PEDMOVE_WALK) {
                ped->Say(45);
            }
        }

        if (ped->m_pIntelligence->m_AnotherStaticCounter > 30) {
            if (m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr)) {
                return CreateSubTask(ped, TASK_SIMPLE_SCRATCH_HEAD);
            }
        }
    }
    return m_pSubTask;
}

void CTaskComplexWander::UpdateDir_Reversed(CPed* ped) {
    uint8 newDir = m_nDir;
    if (m_NextNode.IsAreaValid())
    {
        if (ThePaths.m_pPathNodes[m_NextNode.m_wAreaId])
        {
            CPathNode* pathNodes = ThePaths.m_pPathNodes[m_NextNode.m_wAreaId];
            CPathNode* pathNode = &pathNodes[m_NextNode.m_wNodeId];
            if (pathNode) {
                if (pathNode->m_nNumLinks >= 3 && CTimer::GetFrameCounter() != m_nLastUpdateDirFrameCount && m_bWanderSensibly) {
                    m_nLastUpdateDirFrameCount = CTimer::GetFrameCounter();
                    uint8 remainder = (3 * CTimer::GetFrameCounter() + ped->m_nRandomSeed) % 100;
                    if (remainder <= 90u) {
                        if (remainder > 80u) {
                            newDir = (newDir + 10) % 8;
                        }
                    } else {
                        newDir = (m_nDir + 6) % 8;
                    }
                }
            }
        }
    }

    if (newDir != m_nDir) {
        uint8 outDir;
        UpdatePathNodes(ped, newDir, m_LastNode, m_NextNode, outDir);

        uint8 currentDir = m_nDir;
        uint8 theDir = outDir;
        if (outDir <= currentDir) {
            theDir = m_nDir;
        }

        if (theDir == currentDir) {
            currentDir = outDir;
        }

        if (((theDir - currentDir + 8) % 8) <= 3u) {
            m_nDir = newDir;
        }
    }
}

void CTaskComplexWander::UpdatePathNodes_Reversed(const CPed* ped, uint8 dir, CNodeAddress& originNode, CNodeAddress& targetNode, uint8& outDir) {
    originNode = targetNode;
    targetNode.m_wAreaId = (uint16)-1;
    const CVector& pos = ped->GetPosition();
    ThePaths.FindNextNodeWandering(PATH_TYPE_BOATS, pos, &originNode, &targetNode, dir, &outDir);
}

// 0x671CB0
CTask* CTaskComplexWander::CreateSubTask(CPed* ped, int32 taskId) {
    if (taskId > TASK_COMPLEX_LEAVE_CAR) {
        switch (taskId) {
        case TASK_SIMPLE_CAR_DRIVE_TIMED: {
            return new CTaskSimpleCarDriveTimed(ped->m_pVehicle, 2000);
        }
        case TASK_SIMPLE_GO_TO_POINT: {
            CVector outTargetPos;
            ComputeTargetPos(ped, outTargetPos, m_NextNode);
            return new CTaskSimpleGoToPoint(m_nMoveState, outTargetPos, m_fTargetRadius, false, false);
        }
        case TASK_FINISHED: {
            break;
        }
        default: {
            return nullptr;
        }
        }
    } else {
        switch (taskId) {
        case TASK_COMPLEX_LEAVE_CAR: {
            return new CTaskComplexLeaveCar(ped->m_pVehicle, 0, 0, true, false);
        }
        case TASK_COMPLEX_OBSERVE_TRAFFIC_LIGHTS_AND_ACHIEVE_HEADING: {
            return new CTaskComplexObserveTrafficLightsAndAchieveHeading(2000, ComputeTargetHeading(ped));
        }
        case TASK_COMPLEX_CROSS_ROAD_LOOK_AND_ACHIEVE_HEADING: {
            return new CTaskComplexCrossRoadLookAndAchieveHeading(2000, ComputeTargetHeading(ped));
        }
        case TASK_SIMPLE_SCRATCH_HEAD: {
            return new CTaskSimpleScratchHead();
        }
        default: {
            return nullptr;
        }
        }
    }
    return nullptr;
}

// 0x66F530
float CTaskComplexWander::ComputeTargetHeading(CPed* ped)
{
    auto position = ThePaths.TakeWidthIntoAccountForWandering(m_NextNode, ped->m_nRandomSeed);
    position -= ped->GetPosition();
    float radianAngle = CGeneral::GetRadianAngleBetweenPoints(position.x, position.y, 0.0f, 0.0f);
    return CGeneral::LimitRadianAngle(radianAngle);
}

// 0x669F60
void CTaskComplexWander::ComputeTargetPos(const CPed* ped, CVector& outTargetPos, const CNodeAddress& targetNodeAddress) {
    outTargetPos = ThePaths.TakeWidthIntoAccountForWandering(targetNodeAddress, ped->m_nRandomSeed);
    outTargetPos.z += 1.0f;
}

// 0x669F30
bool CTaskComplexWander::ValidNodes() const {
    if (m_NextNode.IsAreaValid() && m_LastNode.IsAreaValid()) {
        if (m_NextNode.m_wAreaId != m_LastNode.m_wAreaId || m_NextNode.m_wNodeId != m_LastNode.m_wNodeId) {
            return true;
        }
    }
    return false;
}

// 0x674560
void CTaskComplexWander::ScanForBlockedNodes(CPed* ped) {
    if (m_pSubTask->GetTaskType() == TASK_SIMPLE_GO_TO_POINT && m_NextNode.IsAreaValid()) {
        if (ScanForBlockedNode(ped, m_NextNode)) {
            m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_LEISURE, nullptr);

            uint8 outDir = 0;
            UpdatePathNodes(ped, m_nDir, m_LastNode, m_NextNode, outDir);
            if (ScanForBlockedNode(ped, m_NextNode) || &m_NextNode == &m_LastNode) {
                m_bAllNodesBlocked = 1;
            }
        }
    }
}

// 0x671EF0
bool CTaskComplexWander::ScanForBlockedNode(CPed* ped, const CNodeAddress& targetNodeAddress) {
    auto outVec = ThePaths.TakeWidthIntoAccountForWandering(targetNodeAddress, ped->m_nRandomSeed);
    CVector2D distance = outVec - ped->GetPosition();
    if (3.0f * 3.0f >= distance.SquaredMagnitude()) {
        CPed* closestPed = ped->m_pIntelligence->GetPedScanner().m_pClosestEntityInRange->AsPed();
        if (ScanForBlockedNode(&outVec, closestPed))
        {
            return true;
        }

        CVehicle* closestVehicle = ped->GetIntelligence()->m_vehicleScanner.m_pClosestEntityInRange->AsVehicle();
        if (ScanForBlockedNode(&outVec, closestVehicle))
        {
            return true;
        }
    }
    return false;
}

// 0x66F4C0
bool CTaskComplexWander::ScanForBlockedNode(CVector* position, CEntity* entity) {
    if (!entity)
        return false;

    CVector2D distance = *position - entity->GetPosition();
    float fRadius = CModelInfo::GetModelInfo(entity->m_nModelIndex)->GetColModel()->GetBoundRadius() + 1.0f;
    if (fRadius * fRadius > distance.SquaredMagnitude())
        return true;

    return false;
}

// 0x673D00
CTaskComplexWander* CTaskComplexWander::GetWanderTaskByPedType(CPed* ped) {
    uint8 randomDir = CGeneral::GetRandomNumberInRange(0, 8);
    switch (ped->m_nPedType) {
    case PED_TYPE_COP:
        return new CTaskComplexWanderCop(PEDMOVE_WALK, randomDir);
    case PED_TYPE_MEDIC:
        return new CTaskComplexWanderMedic(PEDMOVE_WALK, randomDir);
    case PED_TYPE_CRIMINAL:
        return new CTaskComplexWanderCriminal(PEDMOVE_WALK, randomDir);
    case PED_TYPE_PROSTITUTE:
        return new CTaskComplexWanderProstitute(PEDMOVE_WALK, randomDir);
    default:
        return new CTaskComplexWanderStandard(PEDMOVE_WALK, randomDir);
    }
}
