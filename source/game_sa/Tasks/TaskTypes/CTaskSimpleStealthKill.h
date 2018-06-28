/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskSimple.h"
#include "CPed.h"
#include "CAnimBlendAssociation.h"

class CTaskSimpleStealthKill : public CTaskSimple
{
protected:
    CTaskSimpleStealthKill(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    bool m_bKeepTargetAlive;
private:
    char _pad[3];
public:
    CPed *m_pTarget;
    int m_nAssocGroupId;
    bool b_bIsAborting;
    bool b_bIsFinished;
private:
    char _pad2[2];
public:
    CAnimBlendAssociation *m_pAnim;
    unsigned int m_nTime;

    CTaskSimpleStealthKill(bool bKeepTargetAlive,CPed *pTarget,int nAssocGroupId);
};

VALIDATE_SIZE(CTaskSimpleStealthKill, 0x20);

