#pragma once

#include "Vector.h"
#include "TaskSimpleRunNamedAnim.h"

constexpr auto STAND_STILL_TIME = 20000; // 0x86DB24

class CTaskSimpleSlideToCoord : public CTaskSimpleRunNamedAnim {
public:
    CVector m_SlideToPos{};
    float   m_fAimingRotation{};
    float   m_fRadius{};
    uint8   m_bShouldProcessStandStill : 1{true};
    uint8   m_bHasAnim : 1{};
    uint32  m_Time{(uint32)-1};

public:
    static constexpr auto Type = TASK_SIMPLE_SLIDE_TO_COORD;

    CTaskSimpleSlideToCoord(CVector const& pos, float fAimingRotation, float radius);
    CTaskSimpleSlideToCoord(CVector const& slideToPos, float aimingRotation, float radius, char const* animBlockName, char const* animGroupName, uint32 animFlags, float animBlendDelta, bool isActiveSequence, uint32 time);
    ~CTaskSimpleSlideToCoord() = default;

    CTask* Clone() override;
    eTaskType GetTaskType() override { return Type; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleSlideToCoord* Constructor(CVector const& pos, float fAimingRotation, float radius) { this->CTaskSimpleSlideToCoord::CTaskSimpleSlideToCoord(pos, fAimingRotation, radius); return this; }
    CTaskSimpleSlideToCoord* Constructor(CVector const& pos, float aimRot, float radius, char const* animName, char const* fileName, int32 flags, float frameDelta, bool isActiveSequence, int32 time) { this->CTaskSimpleSlideToCoord::CTaskSimpleSlideToCoord(pos, aimRot, radius, animName, fileName, flags, frameDelta, isActiveSequence, time); return this; }
    CTaskSimpleSlideToCoord* Destructor() { this->CTaskSimpleSlideToCoord::~CTaskSimpleSlideToCoord(); return this; }
    CTask* Clone_Reversed() { return CTaskSimpleSlideToCoord::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskSimpleSlideToCoord::GetTaskType(); }
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent const* event) { return CTaskSimpleSlideToCoord::MakeAbortable(ped, priority, event); }
    bool ProcessPed_Reversed(CPed* ped) { return CTaskSimpleSlideToCoord::ProcessPed(ped); }
};
VALIDATE_SIZE(CTaskSimpleSlideToCoord, 0x80);
