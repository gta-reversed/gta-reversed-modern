/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CTaskSimpleAnim.h"
#include "CAnimBlendAssociation.h"

class CTaskSimpleRunAnim : public CTaskSimpleAnim {
public:
    AssocGroupId m_nAnimGroup;
    AnimationId m_nAnimId;
    float m_fBlendDelta;
    unsigned short m_nTaskType;
    char _pad[2];

public:
    CTaskSimpleRunAnim(AssocGroupId animGroup, AnimationId animId, float fBlendDelta, bool bHoldLastFrame);
    CTaskSimpleRunAnim(AssocGroupId animGroup, AnimationId animId, float fBlendDelta, int nTaskType, const char* taskName _IGNORED_, bool bHoldLastFrame);

    CTask* Clone() override;
    eTaskType GetId() override { return static_cast<eTaskType>(m_nTaskType); }
    bool ProcessPed(CPed* ped) override;

    void StartAnim(CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleRunAnim* Constructor(AssocGroupId animGroup, AnimationId animId, float fBlendDelta, bool bHoldLastFrame);
    CTaskSimpleRunAnim* Constructor2(AssocGroupId animGroup, AnimationId animId, float fBlendDelta, int nTaskType, const char* taskName _IGNORED_, bool bHoldLastFrame);

    CTask* Clone_Reversed();
    bool ProcessPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskSimpleRunAnim, 0x20);
