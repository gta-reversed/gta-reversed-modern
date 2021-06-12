/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskSimpleAnim.h"
#include "CAnimBlendAssociation.h"


class  CTaskSimpleRunAnim : public CTaskSimpleAnim {
public:
    unsigned int m_nAnimGroup; // see eAnimGroup
    unsigned int m_nAnimId; // see eAnimID
    float m_fBlendDelta;
    unsigned short m_nTaskType;
private:
    short __pad;
private:
    CTaskSimpleRunAnim* Constructor(unsigned int animGroup, unsigned int animID, float fBlendDelta, bool bHoldLastFrame);
    CTaskSimpleRunAnim* Constructor2(unsigned int animGroup, unsigned int animID, float fBlendDelta, unsigned int nTaskType,
        char* pTaskName, bool bHoldLastFrame);
public:
    CTaskSimpleRunAnim(unsigned int animGroup, unsigned int animID, float fBlendDelta, unsigned int nTaskType,
        char* pTaskName _IGNORED_, bool bHoldLastFrame);
    CTaskSimpleRunAnim(unsigned int animGroup, unsigned int animID, float fBlendDelta, bool bHoldLastFrame);

    static void InjectHooks();

    CTask* Clone() override;
    eTaskType GetId() override { return static_cast<eTaskType>(m_nTaskType); }
    bool ProcessPed(CPed* ped) override;

    CTask* Clone_Reversed();
    bool ProcessPed_Reversed(CPed* ped);

    void StartAnim(CPed* ped);
};

VALIDATE_SIZE(CTaskSimpleRunAnim, 0x20);
