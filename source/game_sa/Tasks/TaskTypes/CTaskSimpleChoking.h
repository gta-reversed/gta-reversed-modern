/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskSimple.h"
#include "CAnimBlendAssociation.h"


class  CTaskSimpleChoking : public CTaskSimple {
protected:
    CTaskSimpleChoking(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    CPed*      m_pAttacker;
    CAnimBlendAssociation*                      m_pAnim;
    unsigned int                      m_nTimeRemaining;
    unsigned int                      m_nTimeStarted;
    bool                       m_bIsTeargas;
    bool                        m_bIsFinished;

    CTaskSimpleChoking(CPed* pAttacker, bool bIsTeargas);
    void UpdateChoke(CPed* pVictim, CPed* pAttacker, bool bIsTeargas);

};

VALIDATE_SIZE(CTaskSimpleChoking, 0x1C);
