#include "StdInc.h"
#include "TaskComplexSeekEntity.h"
#include "TaskSimpleTired.h"
#include "TaskComplexFollowNodeRoute.h"
#include "extensions/utility.hpp"
#include "TaskComplexGoToPointAndStandStill.h"
#include "TaskSimpleStandStill.h"
#include "PedPlacement.h"

// 0x493730
/*!
* @param v
*/
template<typename T>
CTaskComplexSeekEntity<T>::CTaskComplexSeekEntity(
    CEntity* entity, // May be null
    int32    scanInterval,
    int32    seekInterval,
    float    maxEntityDist2D,
    float    moveStateRadius,
    float    unk2,
    bool     flag0,
    bool     flag1
) :
    m_entity{entity},
    m_seekInterval{ seekInterval },
    m_scanInterval{ scanInterval },
    m_maxEntityDist2D{maxEntityDist2D},
    m_moveStateRadius{moveStateRadius},
    m_unk2{unk2},
    m_flag0x1{flag0},
    m_flag0x2{flag1}
{
    CEntity::SafeRegisterRef(m_entity);
}

// 0x493890
template<typename T>
CTaskComplexSeekEntity<T>::~CTaskComplexSeekEntity() {
    CEntity::SafeCleanUpRef(m_entity);
}

template<typename T>
CTask* CTaskComplexSeekEntity<T>::CreateSubTask(eTaskType type, CPed* ped) {
    return nullptr;
}

// 0x495FB0
template<typename T>
CTask* CTaskComplexSeekEntity<T>::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x495FB0, CTaskComplexSeekEntity<T>*>(this);
}

// 0x493800
template<typename T>
eTaskType CTaskComplexSeekEntity<T>::GetTaskType() {
    return plugin::CallMethodAndReturn<eTaskType, 0x493800, CTaskComplexSeekEntity<T>*>(this);
}

// 0x493810
template<typename T>
bool CTaskComplexSeekEntity<T>::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x493810, CTaskComplexSeekEntity<T>*, CPed*, eAbortPriority, CEvent const*>(this, ped, priority, event);
}

// 0x496080
template<typename T>
CTask* CTaskComplexSeekEntity<T>::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x496080, CTaskComplexSeekEntity<T>*, CPed*>(this, ped);
}

// 0x496600
template<typename T>
CTask* CTaskComplexSeekEntity<T>::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x496600, CTaskComplexSeekEntity<T>*, CPed*>(this, ped);
}

// 0x496760
template<typename T>
CTask* CTaskComplexSeekEntity<T>::ControlSubTask(CPed* ped) {
    // Boat in contact with both peds (that is, in case m_entity is a ped)
    const auto commonBoat = [this, ped]() -> CBoat* {
        if (!m_entity || !m_entity->IsPed()) {
            return nullptr;
        }

        const auto toSeekPed = m_entity->AsPed();

        if (!CPedGroups::AreInSameGroup(toSeekPed, ped)) {
            return nullptr;
        }

        if (toSeekPed->physicalFlags.bSubmergedInWater) {
            return nullptr;
        }

        for (const auto entity : { toSeekPed->m_standingOnEntity, toSeekPed->m_pContactEntity }) {
            if (entity && entity->IsVehicle()) {
                if (ped->m_standingOnEntity == entity || ped->m_pContactEntity == entity) {
                    if (entity->AsVehicle()->IsBoat()) {
                        return entity->AsBoat();
                    }
                }
            }
        }

        return nullptr;
    }();

    if (ped->m_pAttachedTo && !commonBoat) {
        ped->DettachPedFromEntity();
    }

    const auto subTaskType = m_pSubTask->GetTaskType();

    if (
           ped->m_pAttachedTo // From 0x496821
        || !commonBoat
        || subTaskType == TASK_SIMPLE_STAND_STILL
        || m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr)
    ) {
        notsa::AutoCallOnDestruct makePedTalkOnReturn{ [this, ped] {
            if (m_entity && m_entity->IsPed()) {
                if (m_entity->AsPed()->IsPlayer()) { // Entity to seek is a player
                    if (FindPlayerPed()->GetGroup().GetMembership().IsFollower(ped)) { // And ped is part of the player's group
                        if (ped->IsJoggingOrFaster()) {
                            if (((uint16)CTimer::GetFrameCounter() + ped->m_nRandomSeed) % 16384 == 0) {
                                ped->Say(91);
                            }
                        }
                    }
                }
            }
        }};


        switch (subTaskType) {
        case TASK_COMPLEX_FOLLOW_NODE_ROUTE:
        case TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL:
            break;
        default:
            return nullptr;
        }

        if (!m_entity) {
            return m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr) ? nullptr : m_pSubTask;
        }

        if (m_scanTimer.IsOutOfTime()) {
            if (!m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr)) {
                return m_pSubTask;
            }

            if (!m_flag0x1) {
                return nullptr;
            }

            return new CTaskSimpleTired{ 1000u };
        }

        if (!m_seekTimer.IsOutOfTime()) {
            return m_pSubTask;
        }

        m_seekTimer.Start(m_seekInterval);

        CVector seekPos{};
        m_entitySeekPosCalculator.ComputeEntitySeekPos(*ped, *m_entity, seekPos);
        const auto pedToSeekPosDist2dSq = (ped->GetPosition() - seekPos).SquaredMagnitude2D();

        if (subTaskType == TASK_COMPLEX_FOLLOW_NODE_ROUTE) {
            if (m_minEntityDist2D == 0.f || pedToSeekPosDist2dSq >= sq(m_minEntityDist2D - 1.f)) {
                static_cast<CTaskComplexFollowNodeRoute*>(m_pSubTask)->SetTarget(ped, seekPos, m_maxEntityDist2D, m_moveStateRadius, m_unk2, false);
            } else if (m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr)) {
                return CreateSubTask(TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL, ped);
            }
        } else {
            const auto subTaskStandStill = static_cast<CTaskComplexGoToPointAndStandStill*>(m_pSubTask);
            if (subTaskStandStill->m_b05) {
                return m_pSubTask;      
            } else if (m_minEntityDist2D == 0.f || pedToSeekPosDist2dSq <= sq(m_minEntityDist2D + 1.f)) {
                subTaskStandStill->GoToPoint(seekPos, m_maxEntityDist2D, m_moveStateRadius, false);
            } else if (m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr)) {
                return CreateSubTask(TASK_COMPLEX_FOLLOW_NODE_ROUTE, ped);
            }
        }
        return m_pSubTask;
    }

    // Process ped to boat attachment

    auto& boatPos      = commonBoat->GetPosition();
    auto  pedToBoat    = ped->GetPosition() - boatPos;
    auto  pedToBoatDir = Normalized(pedToBoat);

    auto newPedPos = boatPos - (pedToBoat - pedToBoatDir * 0.25f);
    (void)CPedPlacement::FindZCoorForPed(newPedPos); // Omitting `if` check here, it's useless
    
    ped->AttachPedToEntity(
        commonBoat,
        Multiply3x3(Invert(commonBoat->GetMatrix()), newPedPos - boatPos),
        CGeneral::LimitRadianAngle(CGeneral::GetRadianAngleBetweenPoints(pedToBoatDir, {})),
        0.2f,
        ped->GetActiveWeapon().m_nType
    );

    return new CTaskSimpleStandStill{ 2000 };
}
