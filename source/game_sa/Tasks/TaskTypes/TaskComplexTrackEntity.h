#pragma once

#include "TaskComplex.h"
#include "Vector.h"
#include "TaskTimer.h"

class CEntity;

class CTaskComplexTrackEntity : public CTaskComplex {
public:
    CEntity*   m_Entity;
    CVector    m_OffsetPos;
    bool       m_UseSprint;
    int32      m_GiveUpTime;
    float      m_NodeRouteDist;
    float      m_GiveUpDist;
    bool       m_bLocalOffset;
    CTaskTimer m_Timer;
    float      m_fMoveBlendRatio;
    float      m_fTargetBlendRatio;
    CVector    m_TargetPos;
    float      m_fDistToTargetSq;
    bool       m_bEntityStopped;

public:
    constexpr static auto Type = TASK_COMPLEX_TRACK_ENTITY;

    CTaskComplexTrackEntity(CEntity* entity, CVector offsetPos, bool useSprint, int32 giveUpTime, float nodeRouteDist, float giveUpDist, bool localOffset);
    ~CTaskComplexTrackEntity() override;

    eTaskType GetTaskType() override { return Type; }
    CTask*    Clone() override { return new CTaskComplexTrackEntity{*this}; }
    bool      MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    CTask*    CreateNextSubTask(CPed* ped) override;
    CTask*    CreateFirstSubTask(CPed* ped) override;
    CTask*    ControlSubTask(CPed* ped) override;

    void SetOffsetPos(CVector pos);
    void CalcTargetPos(CPed* ped);
    void CalcMoveRatio(CPed* ped);

    static void InjectHooks();
    CTaskComplexTrackEntity* Constructor(CEntity* entity, CVector posn, uint8 a6, int32 a7, float rangeMin, float rangeMax, uint8 a10) { this->CTaskComplexTrackEntity::CTaskComplexTrackEntity(entity,  posn,  a6,  a7,  rangeMin,  rangeMax,  a10); return this; }
    CTaskComplexTrackEntity* Destructor() { this->CTaskComplexTrackEntity::~CTaskComplexTrackEntity(); return this; }
};
VALIDATE_SIZE(CTaskComplexTrackEntity, 0x58);
