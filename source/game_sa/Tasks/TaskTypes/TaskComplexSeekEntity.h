#pragma once

#include "TaskComplex.h"
#include "TaskTimer.h"
#include "Ped.h" // eMoveState
#include "EntitySeekPosCalculator.h"
#include "EntitySeekPosCalculatorRadiusAngleOffset.h"

template <typename EntitySeekT>
    //requires (std::is_base_of_v<CEntitySeekPosCalculator, EntitySeekT>)
class CTaskComplexSeekEntity : public CTaskComplex {
    CEntity* m_entityToSeek{};
    int32 m_seekInterval{};
    int32 m_scanInterval{};
    float m_maxEntityDist2D{};
    float m_moveStateRadius{};
    float m_minEntityDist2D{};
    float m_unk2{}; // TODO: Used as the value for `CTaskComplexFollowNodeRoute::m_fUnkn2`
    CTaskTimer m_seekTimer{};
    CTaskTimer m_scanTimer{};
    EntitySeekT m_entitySeekPosCalculator{};
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
    */
    static constexpr auto Type = eTaskType::TASK_COMPLEX_SEEK_ENTITY;

    CTaskComplexSeekEntity(
        CEntity* entity,
        int32    taskTimer2Interval,
        int32    taskTimer1Interval,
        float    maxEntityDist2D,
        float    unk1,
        float    unk2,
        bool     flag0,
        bool     flag1
    );
    CTaskComplexSeekEntity(const CTaskComplexSeekEntity&);
    ~CTaskComplexSeekEntity() override;

    CTask* CreateSubTask(eTaskType type, CPed* ped);

    CTask*    Clone() override { return new CTaskComplexSeekEntity{ *this }; }
    eTaskType GetTaskType() override { return Type; }
    bool      MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    CTask*    CreateNextSubTask(CPed* ped) override;
    CTask*    CreateFirstSubTask(CPed* ped) override;
    CTask*    ControlSubTask(CPed* ped) override;

    // NOTSA Helpers
    CVector GetSeekPos(CPed* ped);
    CTask* CreateSubTaskWhenPedIsTooFarFromEntity(CPed* ped, float pedToSeekPosDist2DSq);

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
