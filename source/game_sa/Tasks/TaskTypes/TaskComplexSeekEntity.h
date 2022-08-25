#pragma once

#include "TaskComplex.h"
#include "TaskTimer.h"
#include "EntitySeekPosCalculator.h"
#include "EntitySeekPosCalculatorRadiusAngleOffset.h"

template <typename EntitySeekT>
    //requires (std::is_base_of_v<CEntitySeekPosCalculator, EntitySeekT>)
class CTaskComplexSeekEntity : public CTaskComplex {
    CEntity* m_entity{};
    int32 m_seekInterval{};
    int32 m_scanInterval{};
    float m_maxEntityDist2D{};
    float m_moveStateRadius{};
    float m_minEntityDist2D{};
    float m_unk2{};
    CTaskTimer m_seekTimer{};
    CTaskTimer m_scanTimer{};
    EntitySeekT m_entitySeekPosCalculator{};
    uint32 m_unk3{6};
    bool m_flag0x1 : 1{};
    bool m_flag0x2 : 1{};
    bool m_flag0x4 : 1{};
    bool m_flag0x8 : 1{};
public:
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
    ~CTaskComplexSeekEntity() override;

    CTask* CreateSubTask(eTaskType type, CPed* ped);

    CTask* Clone() override;
    eTaskType GetTaskType() override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

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
