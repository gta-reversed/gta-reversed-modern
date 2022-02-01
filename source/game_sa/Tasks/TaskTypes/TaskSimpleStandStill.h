/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "TaskSimple.h"
#include "TaskTimer.h"

class CTaskSimpleStandStill : public CTaskSimple {
public:
    int32 m_nTime;
    CTaskTimer m_timer;
    bool m_bLooped;
    bool m_bUseAnimIdleStance;
private:
    char _pad[2];
public:
    float m_fBlendData;

    static void InjectHooks();

    CTaskSimpleStandStill(int32 nTime, bool Looped, bool bUseAnimIdleStance, float fBlendData);
    ~CTaskSimpleStandStill();
private:
	CTaskSimpleStandStill* Constructor(int32 nTime, bool Looped, bool bUseAnimIdleStance, float fBlendData);
public:
    CTask* Clone()  override;
    eTaskType GetTaskType() override { return TASK_SIMPLE_STAND_STILL; };
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

    CTask* Clone_Reversed();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskSimpleStandStill, 0x20);