#pragma once

#include <concepts>

#include "TaskComplex.h"
#include "TaskTimer.h"
#include "Ped.h" // TODO: eMoveState (When possible move to an enum file)
#include "extensions/utility.hpp"
#include "PedPlacement.h"
#include "TaskSimpleCarDriveTimed.h"
#include "TaskSimpleTired.h"
#include "TaskComplexFollowNodeRoute.h"
#include "TaskComplexGoToPointAndStandStill.h"
#include "TaskSimpleCarDrive.h"
#include "TaskComplexLeaveCar.h"
#include "TaskComplexSequence.h"
#include "TaskComplexTurnToFaceEntityOrCoord.h"
#include "TaskSimpleStandStill.h"
#include "TaskSimpleTired.h"
#include "PosCalculators/EntitySeekPosCalculator.h"

template <std::derived_from<CEntitySeekPosCalculator> T_PosCalc>
class NOTSA_EXPORT_VTABLE CTaskComplexSeekEntity : public CTaskComplex {
    CEntity* m_entityToSeek{};
    int32 m_seekInterval{};
    int32 m_scanInterval{};
    float m_maxEntityDist2D{};
    float m_moveStateRadius{};
    float m_minEntityDist2D{};
    float m_unk2{}; // TODO: Used as the value for `CTaskComplexFollowNodeRoute::m_fUnkn2`
    CTaskTimer m_seekTimer{};
    CTaskTimer m_scanTimer{};
    T_PosCalc m_entitySeekPosCalculator{};
    eMoveState m_moveState{ PEDMOVE_RUN };
    bool m_flag0x1 : 1{};
    bool m_faceSeekEntityAfterReachingIt : 1{};
    bool m_hasReachedSeekEntity : 1{}; /// True when the distance between the `GetSeekPos()` and the `ped` is less than `m_maxEntityDist2D`
    bool m_flag0x8 : 1{};
public:
    /*!
    * NOTE: Since this task is templated but uses the same task type for all templated tasks
    *       our template magic stuff in TaskManager might not work properly with it,
    *       because at runtime all templated tasks will have the same type.
    * NOTE: I commented this out for now, this way there'll be a compile time error (as Type won't be defined)
    */
    //static constexpr auto Type = eTaskType::TASK_COMPLEX_SEEK_ENTITY;

    CTaskComplexSeekEntity(
        CEntity*  entity,
        int32     scanInterval,
        int32     seekInterval,
        float     maxEntityDist2D,
        float     moveStateRadius,
        float     unk2,
        bool      flag0,
        bool      faceSeekEntityAfterReachingIt,
        T_PosCalc seekPosCalculator = {} // NOTSA
    ) :
        m_entityToSeek{ entity },
        m_seekInterval{ seekInterval },
        m_scanInterval{ scanInterval },
        m_maxEntityDist2D{ maxEntityDist2D },
        m_moveStateRadius{ moveStateRadius },
        m_unk2{ unk2 },
        m_flag0x1{ flag0 },
        m_faceSeekEntityAfterReachingIt{ faceSeekEntityAfterReachingIt },
        m_entitySeekPosCalculator{ seekPosCalculator }
    {
        CEntity::SafeRegisterRef(m_entityToSeek);
    }

    CTaskComplexSeekEntity(const CTaskComplexSeekEntity& o) :
        m_entityToSeek{ o.m_entityToSeek },
        m_seekInterval{ o.m_seekInterval },
        m_scanInterval{ o.m_scanInterval },
        m_maxEntityDist2D{ o.m_maxEntityDist2D },
        m_moveStateRadius{ o.m_moveStateRadius },
        m_unk2{ o.m_unk2 },
        m_entitySeekPosCalculator{ o.m_entitySeekPosCalculator },
        m_minEntityDist2D{ o.m_minEntityDist2D },
        m_moveState{ o.m_moveState },
        m_flag0x1{ o.m_flag0x1 },
        m_faceSeekEntityAfterReachingIt{ true },
        m_hasReachedSeekEntity{ o.m_hasReachedSeekEntity }
    {
        CEntity::SafeRegisterRef(m_entityToSeek);
    }

    ~CTaskComplexSeekEntity() override {
        CEntity::SafeCleanUpRef(m_entityToSeek);
    }

    CTask* CreateSubTask(eTaskType type, CPed* ped) {
        switch (type) {
        case TASK_FINISHED:
            return nullptr;
        case TASK_COMPLEX_TURN_TO_FACE_ENTITY:
            return new CTaskComplexTurnToFaceEntityOrCoord{ m_entityToSeek };
        case TASK_COMPLEX_FOLLOW_NODE_ROUTE:
            return new CTaskComplexFollowNodeRoute{
                (int32)m_moveState,
                GetSeekPos(ped),
                m_maxEntityDist2D,
                m_moveStateRadius,
                m_unk2,
                false,
                -1,
                true
            };
        case TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL:
            return new CTaskComplexGoToPointAndStandStill{
                m_moveState,
                GetSeekPos(ped),
                m_maxEntityDist2D,
                m_moveStateRadius,
                false,
                false
            };
        case TASK_SIMPLE_CAR_DRIVE_TIMED:
            return new CTaskSimpleCarDriveTimed{ ped->m_pVehicle, 2000 };
        case TASK_COMPLEX_LEAVE_CAR:
            return new CTaskComplexLeaveCar{ ped->m_pVehicle, TARGET_DOOR_FRONT_LEFT, 0, true, false };
        case TASK_COMPLEX_SEQUENCE: {
            const auto seq = new CTaskComplexSequence{};
            if (m_faceSeekEntityAfterReachingIt) {
                seq->AddTask(new CTaskComplexTurnToFaceEntityOrCoord{ m_entityToSeek });
            }
            seq->AddTask(new CTaskSimpleStandStill{ 100 });
            return seq;
        }
        case TASK_SIMPLE_STAND_STILL:
            return new CTaskSimpleStandStill{ 2000 };
        case TASK_SIMPLE_TIRED:
            return new CTaskSimpleTired{ 1000u };
        default:
            NOTSA_UNREACHABLE();
        }
    }

    CTask* Clone() const override {
        return new CTaskComplexSeekEntity{ *this };
    }

    eTaskType GetTaskType() const override {
        return eTaskType::TASK_COMPLEX_SEEK_ENTITY;
    }

    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override {
        if (priority == ABORT_PRIORITY_LEISURE) {
            m_scanInterval = -1;
            m_scanTimer.SetAsOutOfTime();
        }

        if (m_pSubTask->MakeAbortable(ped, priority, event)) {
            m_seekTimer.SetAsOutOfTime();
            return true;
        }

        return false;
    }

    CTask* CreateNextSubTask(CPed* ped) override {
        switch (m_pSubTask->GetTaskType()) {
        case TASK_COMPLEX_SEQUENCE:
        case TASK_COMPLEX_TURN_TO_FACE_ENTITY:
            return CreateSubTask(TASK_FINISHED, ped);
        case TASK_COMPLEX_FOLLOW_NODE_ROUTE:
        case TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL: {
            if (const auto dist2DSq = (ped->GetPosition() - GetSeekPos(ped)).SquaredMagnitude2D(); dist2DSq > sq(m_maxEntityDist2D)) {
                return CreateSubTaskWhenPedIsTooFarFromEntity(ped, dist2DSq);
            }
            m_hasReachedSeekEntity = true;
            return CreateSubTask(m_faceSeekEntityAfterReachingIt ? TASK_COMPLEX_TURN_TO_FACE_ENTITY : TASK_FINISHED, ped); // Ternary inverted
        }
        case TASK_SIMPLE_CAR_DRIVE_TIMED:
            return CreateFirstSubTask(ped);
        case TASK_COMPLEX_LEAVE_CAR:
            return CreateSubTask(ped->bInVehicle ? TASK_FINISHED : TASK_SIMPLE_CAR_DRIVE_TIMED, ped);
        case TASK_SIMPLE_STAND_STILL:
            return CreateSubTask(TASK_SIMPLE_STAND_STILL, ped);
        case TASK_SIMPLE_TIRED: {
            CTaskSimpleStandStill task{ -1 };
            task.ProcessPed(ped);
            return CreateSubTask(TASK_FINISHED, ped);
        }
        default:
            NOTSA_UNREACHABLE();
        }
    }

    CTask* CreateFirstSubTask(CPed* ped) override {
        m_scanTimer.Start(m_scanInterval);

        if (!m_entityToSeek) {
            return CreateSubTask(TASK_SIMPLE_TIRED, ped);
        }

        if (ped->IsInVehicle()) {
            return CreateSubTask(TASK_COMPLEX_LEAVE_CAR, ped);
        }
 
        if (const auto dist2DSq = (ped->GetPosition() - GetSeekPos(ped)).SquaredMagnitude2D(); dist2DSq > sq(m_maxEntityDist2D)) {
            return CreateSubTaskWhenPedIsTooFarFromEntity(ped, dist2DSq);
        }

        m_hasReachedSeekEntity = true;
        ped->SetMoveState(PEDMOVE_STILL);
        return CreateSubTask(TASK_COMPLEX_SEQUENCE, ped);
    }

    CTask* ControlSubTask(CPed* ped) override {
        // Boat in contact with both peds (that is, in case m_entityToSeek is a ped)
        const auto commonBoat = [this, ped]() -> CBoat* {
            if (!m_entityToSeek || !m_entityToSeek->IsPed()) {
                return nullptr;
            }

            const auto toSeekPed = m_entityToSeek->AsPed();

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
            notsa::ScopeGuard makePedTalkOnReturn{ [this, ped] {
                if (m_entityToSeek && m_entityToSeek->IsPed()) {
                    if (m_entityToSeek->AsPed()->IsPlayer()) { // Entity to seek is a player
                        if (FindPlayerPed()->GetPlayerGroup().GetMembership().IsFollower(ped)) { // And ped is part of the player's group
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

            if (!m_entityToSeek) {
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
            m_entitySeekPosCalculator.ComputeEntitySeekPos(*ped, *m_entityToSeek, seekPos);
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
            (int16)CGeneral::LimitRadianAngle(CGeneral::GetRadianAngleBetweenPoints(pedToBoatDir, {})),
            0.2f,
            ped->GetActiveWeapon().m_Type
        );

        return new CTaskSimpleStandStill{ 2000 };
    }

    // NOTSA Helpers
    CVector GetSeekPos(CPed* ped) {
        CVector seekPos{};
        m_entitySeekPosCalculator.ComputeEntitySeekPos(*ped, *m_entityToSeek, seekPos);
        return seekPos;
    }

    CTask* CreateSubTaskWhenPedIsTooFarFromEntity(CPed* ped, float pedToSeekPosDist2DSq) {
        return CreateSubTask(
            (m_minEntityDist2D == 0.f || pedToSeekPosDist2DSq > sq(m_minEntityDist2D))
                ? TASK_COMPLEX_FOLLOW_NODE_ROUTE
                : TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL,
            ped
        );
    }

protected: // Wrappers for hooks
    // 0x493730
    CTaskComplexSeekEntity* Constructor(
        CEntity* entity,
        int32    taskTimer2Interval,
        int32    taskTimer1Interval,
        float    maxEntityDist2D,
        float    unk1,
        float    unk2,
        bool     flag0,
        bool     flag1
    ) {
        this->CTaskComplexSeekEntity::CTaskComplexSeekEntity(entity, taskTimer1Interval, taskTimer2Interval, maxEntityDist2D, unk1, unk2, flag0, flag1);
        return this;
    }

    // 0x493890
    CTaskComplexSeekEntity* Destructor() {
        this->CTaskComplexSeekEntity::~CTaskComplexSeekEntity();
        return this;
    }
};
