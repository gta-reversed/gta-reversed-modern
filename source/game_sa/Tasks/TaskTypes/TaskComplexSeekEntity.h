#pragma once

#include "TaskComplex.h"
#include "EntitySeekPosCalculatorRadiusAngleOffset.h"
#include "EntitySeekPosCalculatorStandard.h"
#include "EntitySeekPosCalculatorXYOffset.h"

template <typename EntitySeekT>
class CTaskComplexSeekEntity : public CTaskComplex {
    CEntity* m_entity;
    int32 m_taskIntervals[2];
    float m_maxEntityDist2D;
    float m_unk1;
    float m_minEntityDist2D;
    float m_unk2;
    CTaskTimer m_taskTimers[2];
    EntitySeekT m_entitySeekPosCalculator;
    uint32 m_unk3;
    uint8 m_flags;

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

    eTaskType GetTaskType() override;
    CTask* Clone() override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateSubTask(eTaskType type, CPed* ped);

    CTaskComplexSeekEntity* Constructor(CEntity* entity, int32 taskTimer2Interval, int32 taskTimer1Interval, float maxEntityDist2D, float unk1, float unk2, bool flag0, bool flag1) { this->CTaskComplexSeekEntity::CTaskComplexSeekEntity(entity, taskTimer1Interval, taskTimer2Interval, maxEntityDist2D, unk1, unk2, flag0, flag1); return this; }
    CTaskComplexSeekEntity* Destructor() { this->CTaskComplexSeekEntity::~CTaskComplexSeekEntity(); return this; }
};

class CTaskComplexSeekEntity_CEntitySeekPosCalculatorRadiusAngleOffset : public CTaskComplexSeekEntity<CEntitySeekPosCalculatorRadiusAngleOffset> {
public:
    static void InjectHooks();
};
VALIDATE_SIZE(CTaskComplexSeekEntity_CEntitySeekPosCalculatorRadiusAngleOffset, 0x54);

class CTaskComplexSeekEntity_CEntitySeekPosCalculatorStandard : public CTaskComplexSeekEntity<CEntitySeekPosCalculatorStandard> {
public:
    static void InjectHooks();
};
VALIDATE_SIZE(CTaskComplexSeekEntity_CEntitySeekPosCalculatorStandard, 0x4C);

class CTaskComplexSeekEntity_CEntitySeekPosCalculatorXYOffset : public CTaskComplexSeekEntity<CEntitySeekPosCalculatorXYOffset> {
public:
    static void InjectHooks();
};
VALIDATE_SIZE(CTaskComplexSeekEntity_CEntitySeekPosCalculatorXYOffset, 0x58);
