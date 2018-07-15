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
#include "CEntity.h"

enum eClimbHeights : char
{
    CLIMB_NOT_READY = 0,
    CLIMB_GRAB,
    CLIMB_PULLUP,
    CLIMB_STANDUP,
    CLIMB_FINISHED,
    CLIMB_VAULT,
    CLIMB_FINISHED_V
};

class  CTaskSimpleClimb : public CTaskSimple {
protected:
    CTaskSimpleClimb(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    bool m_bIsFinished;
    bool m_bChangeAnimation;
    bool m_bChangePosition;
    bool m_bForceClimb;
    bool m_bInvalidClimb;
    char m_nHeightForAnim;
    char m_nHeightForPos;
    unsigned char m_nSurfaceType;
    char m_nFallAfterVault;
    float m_fHandholdHeading;
    CVector m_vecHandholdPos;
    CEntity *m_pClimbEnt;
    short m_nGetToPosCounter;
    CAnimBlendAssociation* m_pAnim;

    CTaskSimpleClimb(CEntity *pClimbEnt, const CVector &vecTarget, float fHeading, unsigned char nSurfaceType, eClimbHeights nHeight, bool bForceClimb);
    static CEntity * TestForClimb(CPed* pPed, CVector& climbPos, float& fAngle, unsigned char& nSurfaceType, bool theBool);
};

VALIDATE_SIZE(CTaskSimpleClimb, 0x30);
