/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskSimple.h"
#include "AnimBlendAssociation.h"

class NOTSA_EXPORT_VTABLE CTaskSimpleChoking : public CTaskSimple {
public:
    CPed*                  m_pAttacker;
    CAnimBlendAssociation* m_pAnim;
    uint32                 m_nTimeRemaining;
    uint32                 m_nTimeStarted;
    bool                   m_bIsTeargas;
    bool                   m_bIsFinished;

public:
    static constexpr auto Type = TASK_SIMPLE_CHOKING;

    CTaskSimpleChoking(CPed* attacker, bool bIsTeargas);
    void UpdateChoke(CPed* victim, CPed* attacker, bool bIsTeargas);
};

VALIDATE_SIZE(CTaskSimpleChoking, 0x1C);
