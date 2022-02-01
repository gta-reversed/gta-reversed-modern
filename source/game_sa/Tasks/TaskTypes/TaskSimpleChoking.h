/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "TaskSimple.h"
#include "AnimBlendAssociation.h"


class CTaskSimpleChoking : public CTaskSimple {
public:
    CPed*      m_pAttacker;
    CAnimBlendAssociation*                      m_pAnim;
    uint32                      m_nTimeRemaining;
    uint32                      m_nTimeStarted;
    bool                       m_bIsTeargas;
    bool                        m_bIsFinished;

    CTaskSimpleChoking(CPed* pAttacker, bool bIsTeargas);
    void UpdateChoke(CPed* pVictim, CPed* pAttacker, bool bIsTeargas);

};

VALIDATE_SIZE(CTaskSimpleChoking, 0x1C);
