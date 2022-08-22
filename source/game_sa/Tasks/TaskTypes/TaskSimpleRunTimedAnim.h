#pragma once

#include "TaskSimpleAnim.h"
#include "TaskTimer.h"

class CTaskSimpleRunTimedAnim;
class CPed;

class NOTSA_EXPORT_VTABLE CTaskSimpleRunTimedAnim : public CTaskSimpleAnim {
public:
    AssocGroupId m_AnimGroup;
    AnimationId m_AnimId;
    float m_fBlendDelta;
    float m_fBlendOutDelta;
    int32 m_nDurationMs;
    CTaskTimer m_Timer;
    eTaskType m_TaskType;

public:
    CTaskSimpleRunTimedAnim(AssocGroupId groupId, AnimationId animId, float blendDelta, float unused1, int32 durationMs, bool holdLastFrame); // 0x61AB70
    CTaskSimpleRunTimedAnim(AssocGroupId groupId, AnimationId animId, float blendDelta, float unused1, int32 durationMs, uint32 taskId, const char* unused2, bool holdLastFrame); // 0x61ABE0
    ~CTaskSimpleRunTimedAnim() = default;  // 0x48E090


    eTaskType GetTaskType() override { return m_TaskType; }
    CTask* Clone() override { return new CTaskSimpleRunTimedAnim(m_AnimGroup, m_AnimId, m_fBlendDelta, m_fBlendOutDelta, m_nDurationMs, (m_nFlags & 4) >> 2); }
    bool ProcessPed(CPed* ped) override;

    void StartAnim(CPed* ped);

    static void InjectHooks();
    CTaskSimpleRunTimedAnim* Constructor(AssocGroupId groupId, AnimationId animId, float blendDelta, float unused1, uint32 durationMs, bool holdLastFrame) { this->CTaskSimpleRunTimedAnim::CTaskSimpleRunTimedAnim(groupId, animId, blendDelta, unused1, durationMs, holdLastFrame); return this; }
    CTaskSimpleRunTimedAnim* Constructor(AssocGroupId groupId, AnimationId animId, float blendDelta, float unused1, uint32 durationMs, uint32 taskId, const char* unused2, bool holdLastFrame) { this->CTaskSimpleRunTimedAnim::CTaskSimpleRunTimedAnim(groupId, animId, blendDelta, unused1, durationMs, taskId, unused2, holdLastFrame); return this; }
    CTaskSimpleRunTimedAnim* Destructor() { this->CTaskSimpleRunTimedAnim::~CTaskSimpleRunTimedAnim(); return this; }
};
